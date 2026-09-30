#include <bits/stdc++.h>
using namespace std;

// deklarasi struct
struct Peserta {
    string nama;
    int angkatan;
    int kelompok;
};

// batas maks perkelompok
const int MAKS_PESERTA = 7;

// angkatan yang boleh mendaftar
const int ANGKATAN_1 = 25;
const int ANGKATAN_2 = 26;

// deklarasi variabel
Peserta kelompok1[MAKS_PESERTA];
int jumlahPeserta1 = 0;

Peserta kelompok2[MAKS_PESERTA];
int jumlahPeserta2 = 0;

// mengubah string menjadi huruf kecil (untuk pencarian case-insensitive)
string keHurufKecil(string teks) {
    for (size_t i = 0; i < teks.size(); i++) {
        teks[i] = (char)tolower((unsigned char)teks[i]);
    }
    return teks;
}

// membersihkan input jika user memasukkan non-angka
void bersihkanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// fitur 1: daftar Peserta
void daftarPeserta() {
    Peserta pesertaBaru;

    cout << "\n--- Form Pendaftaran ---\n";
    // ulangi seluruh form (nama + angkatan) dari awal sampai angkatan valid
    while (true) {
        cout << "Masukkan Nama     : ";
        cin >> ws;
        getline(cin, pesertaBaru.nama);

        cout << "Masukkan Angkatan : ";
        if (cin >> pesertaBaru.angkatan &&
            (pesertaBaru.angkatan == ANGKATAN_1 || pesertaBaru.angkatan == ANGKATAN_2)) {
            break;
        }

        // angkatan tidak valid: hapus nama dan mulai pendaftaran dari awal
        bersihkanInput();
        pesertaBaru.nama = "";
        cout << "-> Angkatan tidak valid! Hanya angkatan " << ANGKATAN_1
             << " dan " << ANGKATAN_2 << " yang boleh mendaftar."
             << " Data dihapus, silakan daftar ulang dari awal.\n\n";
    }

    cout << "Pilih Kelompok (1/2): ";
    if (!(cin >> pesertaBaru.kelompok)) {
        bersihkanInput();
        pesertaBaru.kelompok = 0; // akan ditolak sebagai pilihan tidak valid
    }

    // validasi penempatan array
    if (pesertaBaru.kelompok == 1) {
        if (jumlahPeserta1 < MAKS_PESERTA) {
            kelompok1[jumlahPeserta1] = pesertaBaru;
            jumlahPeserta1++;
            cout << "-> Pendaftaran berhasil! Masuk ke Kelompok 1.\n";
        } else {
            cout << "-> Peringatan: Kuota Kelompok 1 sudah penuh!\n";
        }
    } else if (pesertaBaru.kelompok == 2) {
        if (jumlahPeserta2 < MAKS_PESERTA) {
            kelompok2[jumlahPeserta2] = pesertaBaru;
            jumlahPeserta2++;
            cout << "-> Pendaftaran berhasil! Masuk ke Kelompok 2.\n";
        } else {
            cout << "-> Peringatan: Kuota Kelompok 2 sudah penuh!\n";
        }
    } else {
        cout << "-> Peringatan: Pilihan kelompok tidak valid!\n";
    }
}

// fitur 2: menampilkan semua data
void tampilData() {
    cout << "\n--- Data Peserta Study Group ---\n";

    if (jumlahPeserta1 == 0 && jumlahPeserta2 == 0) {
        cout << "Belum ada peserta yang terdaftar.\n";
        return;
    }

    // menampilkan kelompok 1
    cout << "[ Kelompok 1 ]\n";
    if (jumlahPeserta1 == 0) {
        cout << "  (Kosong)\n";
    } else {
        for (int i = 0; i < jumlahPeserta1; i++) {
            cout << "  " << i + 1 << ". " << kelompok1[i].nama
                 << " (Angkatan " << kelompok1[i].angkatan << ")\n";
        }
    }

    // menampilkan kelompok 2
    cout << "\n[ Kelompok 2 ]\n";
    if (jumlahPeserta2 == 0) {
        cout << "  (Kosong)\n";
    } else {
        for (int i = 0; i < jumlahPeserta2; i++) {
            cout << "  " << i + 1 << ". " << kelompok2[i].nama
                 << " (Angkatan " << kelompok2[i].angkatan << ")\n";
        }
    }
}

// fitur 3: mencari data (case-insensitive)
void cariData() {
    if (jumlahPeserta1 == 0 && jumlahPeserta2 == 0) {
        cout << "\n-> Data masih kosong, tidak ada yang bisa dicari.\n";
        return;
    }

    string kataKunci;
    cout << "\nMasukkan nama peserta yang dicari: ";
    cin >> ws;
    getline(cin, kataKunci);

    string kunciKecil = keHurufKecil(kataKunci);
    bool ditemukan = false;

    // cari kelompok 1
    for (int i = 0; i < jumlahPeserta1; i++) {
        if (keHurufKecil(kelompok1[i].nama) == kunciKecil) {
            cout << "-> Ditemukan! '" << kelompok1[i].nama
                 << "' (Angkatan " << kelompok1[i].angkatan
                 << ") berada di Kelompok 1.\n";
            ditemukan = true;
            break; // menghentikan pencarian kalo ketemu
        }
    }

    // lanjut cari kelompok 2
    if (!ditemukan) {
        for (int i = 0; i < jumlahPeserta2; i++) {
            if (keHurufKecil(kelompok2[i].nama) == kunciKecil) {
                cout << "-> Ditemukan! '" << kelompok2[i].nama
                     << "' (Angkatan " << kelompok2[i].angkatan
                     << ") berada di Kelompok 2.\n";
                ditemukan = true;
                break;
            }
        }
    }

    if (!ditemukan) {
        cout << "-> Peserta bernama '" << kataKunci << "' tidak ditemukan.\n";
    }
}

// utama
int main() {
    int pilihan;
    bool jalan = true;

    while (jalan) {
        cout << "\n SISTEM MANAJEMEN STUDY GROUP\n";
        cout << "=================================\n";
        cout << "1. Daftar Peserta\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Cari Data Peserta\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu (1-4): ";

        if (!(cin >> pilihan)) {
            bersihkanInput();
            pilihan = 0; // jatuh ke default
        }

        switch (pilihan) {
            case 1:
                daftarPeserta();
                break;
            case 2:
                tampilData();
                break;
            case 3:
                cariData();
                break;
            case 4:
                cout << "\nTerima kasih!\n";
                jalan = false;
                break;
            default:
                cout << "\n-> Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    }
}