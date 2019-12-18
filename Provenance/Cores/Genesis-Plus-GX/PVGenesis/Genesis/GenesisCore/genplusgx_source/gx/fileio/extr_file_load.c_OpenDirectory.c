#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ ** lastdir; } ;
struct TYPE_7__ {char* filename; scalar_t__ flags; } ;
struct TYPE_6__ {TYPE_1__* entries; } ;
struct TYPE_5__ {scalar_t__* filepath; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  ClearSelector (int) ; 
 int /*<<< orphan*/  GUI_WaitPrompt (char*,char*) ; 
 int MAXJOLIET ; 
 int /*<<< orphan*/  MountDVD () ; 
 int NUM_HISTORY_ENTRIES ; 
 int ParseDirectory () ; 
 int TYPE_DVD ; 
 int TYPE_RECENT ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 TYPE_4__ config ; 
 int deviceType ; 
 int /*<<< orphan*/  fileDir ; 
 int fileType ; 
 TYPE_3__* filelist ; 
 TYPE_2__ history ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rootdir ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

int OpenDirectory(int device, int type)
{
  int max = 0;

  if (device == TYPE_RECENT)
  {
    /* fetch history list */
    int i;
    for(i=0; i < NUM_HISTORY_ENTRIES; i++)
    {
      if(history.entries[i].filepath[0] > 0)
      {
        filelist[i].flags = 0;
        strncpy(filelist[i].filename,history.entries[i].filename, MAXJOLIET-1);
        filelist[i].filename[MAXJOLIET-1] = '\0';
        max++;
      }
      else
      {
        /* Found the end of the list. */
        break;
      }
    }
  }
  else
  {
    /* only DVD hot swap is supported */
    if (device == TYPE_DVD)
    {
      /* try to access root directory */
      DIR *dir = opendir(rootdir[TYPE_DVD]);
      if (dir == NULL)
      {
        /* mount DVD */
        if (!MountDVD()) return 0;
        deviceType = -1;
      }
      else
      {
        closedir(dir);
      }
    }

    /* parse last directory */
    fileDir = config.lastdir[type][device];
    max = ParseDirectory();
    if (max <= 0)
    {
      /* parse root directory */
      strcpy(fileDir, rootdir[device]);
      max = ParseDirectory();
      if (max < 0)
      {
        GUI_WaitPrompt("Error","Unable to open directory !");
        return 0;
      }
      deviceType = -1;
    }
  }

  if (max == 0)
  {
    GUI_WaitPrompt("Error","No files found !");
    return 0;
  }

  /* check if device or file type has changed */
  if ((device != deviceType) || (type != fileType))
  {
    /* reset current types */
    deviceType = device;
    fileType = type;

    /* reset File selector */
    ClearSelector(max);
  }

  return 1;
}