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
typedef  int /*<<< orphan*/  xdgMimeCommand ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  exePath ;
typedef  int /*<<< orphan*/  desktopFilename ;
typedef  int /*<<< orphan*/  desktopFilePath ;
typedef  int /*<<< orphan*/  desktopFile ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Mkdir (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 size_t readlink (char*,char*,int) ; 
 int snprintf (char*,int,char const*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ system (char*) ; 

void Discord_Register(const char* applicationId, const char* command)
{
   FILE* fp;
   int fileLen;
   char xdgMimeCommand[1024];
   char desktopFilename[256];
   char desktopFilePath[1024];
   char desktopFile[2048];
   /* Add a desktop file and update some MIME handlers 
    * so that xdg-open does the right thing. */
   char exePath[1024];
   const char* home = getenv("HOME");
   if (!home)
      return;

   if (!command || !command[0])
   {
      ssize_t size = readlink("/proc/self/exe", exePath, sizeof(exePath));
      if (size <= 0 || size >= (ssize_t)sizeof(exePath))
         return;
      exePath[size] = '\0';
      command = exePath;
   }

   {
      const char* desktopFileFormat = "[Desktop Entry]\n"
         "Name=Game %s\n"
         "Exec=%s\n" /* note: it really wants that %u in there */
         "Type=Application\n"
         "NoDisplay=true\n"
         "Categories=Discord;Games;\n"
         "MimeType=x-scheme-handler/discord-%s;\n";
      fileLen = snprintf(
            desktopFile, sizeof(desktopFile), desktopFileFormat, applicationId, command, applicationId);
      if (fileLen <= 0)
         return;
   }

   snprintf(desktopFilename, sizeof(desktopFilename), "/discord-%s.desktop", applicationId);

   snprintf(desktopFilePath, sizeof(desktopFilePath), "%s/.local", home);
   if (!Mkdir(desktopFilePath))
      return;
   strcat(desktopFilePath, "/share");
   if (!Mkdir(desktopFilePath))
      return;
   strcat(desktopFilePath, "/applications");
   if (!Mkdir(desktopFilePath))
      return;
   strcat(desktopFilePath, desktopFilename);

   fp = fopen(desktopFilePath, "w");
   if (!fp)
      return;

   fwrite(desktopFile, 1, fileLen, fp);
   fclose(fp);

   snprintf(xdgMimeCommand,
         sizeof(xdgMimeCommand),
         "xdg-mime default discord-%s.desktop x-scheme-handler/discord-%s",
         applicationId,
         applicationId);
   if (system(xdgMimeCommand) < 0)
      fprintf(stderr, "Failed to register mime handler\n");
}