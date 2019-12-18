#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  steamPath ;
typedef  int /*<<< orphan*/  command ;
typedef  scalar_t__ LSTATUS ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  Discord_RegisterW (int*,int*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int*,int) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  StringCbPrintfW (int*,int,char*,int*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void Discord_RegisterSteamGame(
      const char* applicationId,
      const char* steamId)
{
   DWORD pathChars, pathBytes, i;
   HKEY key;
   wchar_t steamPath[MAX_PATH];
   wchar_t command[1024];
   wchar_t appId[32];
   wchar_t wSteamId[32];
   MultiByteToWideChar(CP_UTF8, 0, applicationId, -1, appId, 32);
   MultiByteToWideChar(CP_UTF8, 0, steamId, -1, wSteamId, 32);
   LSTATUS status = RegOpenKeyExW(HKEY_CURRENT_USER,
         L"Software\\Valve\\Steam", 0, KEY_READ, &key);
   if (status != ERROR_SUCCESS)
   {
      fprintf(stderr, "Error opening Steam key\n");
      return;
   }

   pathBytes = sizeof(steamPath);
   status    = RegQueryValueExW(key,
         L"SteamExe", NULL, NULL, (BYTE*)steamPath, &pathBytes);
   RegCloseKey(key);
   if (status != ERROR_SUCCESS || pathBytes < 1) {
      fprintf(stderr, "Error reading SteamExe key\n");
      return;
   }

   pathChars = pathBytes / sizeof(wchar_t);
   for (i = 0; i < pathChars; ++i)
   {
      if (steamPath[i] == L'/')
         steamPath[i] = L'\\';
   }

   StringCbPrintfW(command, sizeof(command),
         L"\"%s\" steam://rungameid/%s", steamPath, wSteamId);

   Discord_RegisterW(appId, command);
}