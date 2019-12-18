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
struct dirent {char const* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ envIsHomebrew () ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void get_first_valid_core(char* path_return)
{
   DIR* dir;
   struct dirent* ent;
   const char* extension = envIsHomebrew() ? ".3dsx" : ".cia";

   path_return[0] = '\0';

   dir = opendir("sdmc:/retroarch/cores");
   if (dir != NULL)
   {
      while (ent = readdir(dir))
      {
         if (ent == NULL)
            break;
         if (strlen(ent->d_name) > strlen(extension) && !strcmp(ent->d_name + strlen(ent->d_name) - strlen(extension), extension))
         {
            strcpy(path_return, "sdmc:/retroarch/cores");
            strcat(path_return, "/");
            strcat(path_return, ent->d_name);
            break;
         }
      }
      closedir(dir);
   }
}