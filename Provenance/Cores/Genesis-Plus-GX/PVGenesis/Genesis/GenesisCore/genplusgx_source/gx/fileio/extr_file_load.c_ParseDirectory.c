#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; scalar_t__ d_type; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  FILEENTRIES ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  FileSortCallback ; 
 int MAXFILES ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileDir ; 
 TYPE_1__* filelist ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

int ParseDirectory(void)
{
  int nbfiles = 0;

  /* open directory */
  DIR *dir = opendir(fileDir);
  if (dir == NULL)
  {
    return -1;
  }

  struct dirent *entry = readdir(dir);

  /* list entries */
  while ((entry != NULL)&& (nbfiles < MAXFILES))
  {
    /* filter entries */
    if ((entry->d_name[0] != '.') 
       && strncasecmp(".wav", &entry->d_name[strlen(entry->d_name) - 4], 4) 
       && strncasecmp(".ogg", &entry->d_name[strlen(entry->d_name) - 4], 4) 
       && strncasecmp(".mp3", &entry->d_name[strlen(entry->d_name) - 4], 4))
    {
      memset(&filelist[nbfiles], 0, sizeof (FILEENTRIES));
      sprintf(filelist[nbfiles].filename,"%s",entry->d_name);
      if (entry->d_type == DT_DIR)
      {
        filelist[nbfiles].flags = 1;
      }
      nbfiles++;
    }

    /* next entry */
    entry = readdir(dir);
  }

  /* close directory */
  closedir(dir);

  /* Sort the file list */
  qsort(filelist, nbfiles, sizeof(FILEENTRIES), FileSortCallback);

  return nbfiles;
}