#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct GameTime
{
    int hours;
    int minutes;
    int seconds;
};

struct Price
{
    int value_1;
    int value_2;
    string currency_symbol_v1;
    string currency_symbol_v2;
    Price() : value_1(0), value_2(0) {}
    Price(int v1, int v2) : value_1(v1), value_2(v2) {}
};

enum Platform
{
    Windows,
    MacOS,
    Linux
};

class Game
{
private:
    string _name;
    string _genre;
    Platform _platform;
    GameTime _timePlayed;
    string _author;
    Price _price;

public:
    Game() : _platform(Windows), _timePlayed{ 0, 0, 0 }, _price(0, 0) {}

    Game(string name, string genre, Platform platform, GameTime timePlayed, string author, Price price)
        : _name(name), _genre(genre), _platform(platform), _timePlayed(timePlayed), _author(author), _price(price) {}

    string GetName() const { return _name; }
    string GetGenre() const { return _genre; }
    Platform GetPlatform() const { return _platform; }
    GameTime GetTimePlayed() const { return _timePlayed; }
    string GetAuthor() const { return _author; }
    Price GetPrice() const { return _price; }

    void SetName(string name) { _name = name; }
    void SetGenre(string genre) { _genre = genre; }
    void SetPlatform(Platform platform) { _platform = platform; }
    void SetTimePlayed(GameTime timePlayed) { _timePlayed = timePlayed; }
    void SetAuthor(string author) { _author = author; }
    void SetPrice(Price price) { _price = price; }

    void PrintInfo() const
    {
        cout << "Name: " << _name << endl;
        cout << "Genre: " << _genre << endl;
        cout << "Platform: ";
        switch (_platform)
        {
        case Windows:
            cout << "Windows" << endl;
            break;
        case MacOS:
            cout << "MacOS" << endl;
            break;
        case Linux:
            cout << "Linux" << endl;
            break;
        }
        cout << "Time Played: " << _timePlayed.hours << "h " << _timePlayed.minutes << "m " << _timePlayed.seconds << "s" << endl;
        cout << "Author: " << _author << endl;
        cout << "Price: " << _price.currency_symbol_v1 << _price.value_1 << "." << _price.value_2 << _price.currency_symbol_v2 << endl;
    }
};

class Steam
{
private:
    Game* _games;
    int _gamesCount;

public:
    Steam() : _games(nullptr), _gamesCount(0) {}

    Steam(Game* games, int gamesCount) : _games(games), _gamesCount(gamesCount) {}

    ~Steam()
    {
        delete[] _games;
    }

    void AddGame(Game game)
    {
        Game* newGames = new Game[_gamesCount + 1];
        for (int i = 0; i < _gamesCount; i++)
        {
            newGames[i] = _games[i];
        }
        newGames[_gamesCount] = game;
        _gamesCount++;
        delete[] _games;
        _games = newGames;
    }

    void RemoveGameByName(string name)
    {
        int index = -1;
        for (int i = 0; i < _gamesCount; i++)
        {
            if (_games[i].GetName() == name)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "Game not found!" << endl;
            return;
        }
        RemoveGameByIndex(index);
    }

    void RemoveGameByIndex(int index)
    {
        Game* newGames = new Game[_gamesCount - 1];
        for (int i = 0; i < index; i++)
        {
            newGames[i] = _games[i];
        }
        for (int i = index + 1; i < _gamesCount; i++)
        {
            newGames[i - 1] = _games[i];
        }
        _gamesCount--;
        delete[] _games;
        _games = newGames;
    }

    void SearchGameByName(string name)
    {
        for (int i = 0; i < _gamesCount; i++)
        {
            if (_games[i].GetName() == name)
            {
                _games[i].PrintInfo();
                return;
            }
        }
        cout << "Game not found!" << endl;
    }

    void SearchGameByAuthor(string author)
    {
        for (int i = 0; i < _gamesCount; i++)
        {
            if (_games[i].GetAuthor() == author)
            {
                _games[i].PrintInfo();
                return;
            }
        }
        cout << "Game not found!" << endl;
    }

    void SearchGameByCurrencySymbol(string symbol)
    {
        for (int i = 0; i < _gamesCount; i++)
        {
            if (_games[i].GetPrice().currency_symbol_v1 == symbol)
            {
                _games[i].PrintInfo();
                return;
            }
        }
        cout << "Game not found!" << endl;
    }

    void SortByPrice()
    {
        sort(_games, _games + _gamesCount, [](const Game& a, const Game& b)
            { return a.GetPrice().value_1 < b.GetPrice().value_1; });
    }

    void SortByAuthor()
    {
        sort(_games, _games + _gamesCount, [](const Game& a, const Game& b)
            { return a.GetAuthor() < b.GetAuthor(); });
    }

    void EditGameBySeedKey(int seedKey, string field, string newValue)
    {
        if (seedKey < 0 || seedKey >= _gamesCount)
        {
            cout << "Invalid seed key!" << endl;
            return;
        }

        if (field == "name")
        {
            _games[seedKey].SetName(newValue);
        }
        else if (field == "genre")
        {
            _games[seedKey].SetGenre(newValue);
        }
        else if (field == "author")
        {
            _games[seedKey].SetAuthor(newValue);
        }
        else
        {
            cout << "Invalid field!" << endl;
        }
    }

    void PrintGames()
    {
        for (int i = 0; i < _gamesCount; i++)
        {
            cout << "Game " << i + 1 << ":" << endl;
            _games[i].PrintInfo();
            cout << endl;
        }
    }
};

int main()
{
    Steam steam;
    Game game1("Game1", "Genre1", Windows, { 1, 2, 3 }, "Author1", { 10, 50, "$", "c" });
    Game game2("Game2", "Genre2", MacOS, { 4, 5, 6 }, "Author2", { 20, 60, "$", "c" });
    Game game3("Game3", "Genre3", Linux, { 7, 8, 9 }, "Author3", { 30, 70, "$", "c" });

    steam.AddGame(game1);
    steam.AddGame(game2);
    steam.AddGame(game3);

    cout << "All games: " << endl;
    steam.PrintGames();

    cout << "Searching for Game1:" << endl;
    steam.SearchGameByName("Game1");

    cout << "Searching for author Author2:" << endl;
    steam.SearchGameByAuthor("Author2");

    cout << "Removing Game2 by name:" << endl;
    steam.RemoveGameByName("Game2");
    steam.PrintGames();

    cout << "Sorting games by price:" << endl;
    steam.SortByPrice();
    steam.PrintGames();

    cout << "Editing Game1's name by seed-key:" << endl;
    steam.EditGameBySeedKey(0, "name", "NewGame1");
    steam.PrintGames();

    return 0;
}
