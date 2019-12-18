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

/* Variables and functions */
 int MAXPATHLEN ; 
 size_t TYPE_RECENT ; 
 size_t deviceType ; 
 char* fileDir ; 
 int /*<<< orphan*/ * rootdir ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strtok (char*,char*) ; 

int UpdateDirectory(bool go_up, char *dirname)
{
  /* go up to parent directory */
  if (go_up)
  {
    /* special case */
    if (deviceType == TYPE_RECENT) return 0;

    /* check if we already are at root directory */
    if (!strcmp(rootdir[deviceType], (const char *)fileDir)) return 0;

    int size=0;
    char temp[MAXPATHLEN];

    /* determine last folder name length */
    strcpy(temp, fileDir);
    char *test= strtok(temp,"/");
    while (test != NULL)
    {
      size = strlen(test);
      strncpy(dirname,test,size);
      dirname[size] = 0;
      test = strtok(NULL,"/");
    }

    /* remove last folder from path */
    size = strlen(fileDir) - size;
    fileDir[size - 1] = 0;
  }
  else
  {
    /* by default, simply append folder name */
    sprintf(fileDir, "%s%s/",fileDir, dirname);
  }

  return 1;
}