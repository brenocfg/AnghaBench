#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_16__ {scalar_t__ ram; } ;
struct TYPE_15__ {scalar_t__ status; } ;
struct TYPE_14__ {int /*<<< orphan*/  s_device; int /*<<< orphan*/  s_default; } ;
struct TYPE_13__ {char* filename; } ;
struct TYPE_12__ {TYPE_1__* entries; } ;
struct TYPE_10__ {scalar_t__ boot; } ;
struct TYPE_11__ {TYPE_2__ cartridge; } ;
struct TYPE_9__ {char* filepath; } ;

/* Variables and functions */
 scalar_t__ CD_OPEN ; 
 int /*<<< orphan*/  GUI_MsgBoxClose () ; 
 int /*<<< orphan*/  GUI_MsgBoxOpen (char*,char*,int) ; 
 int /*<<< orphan*/  GUI_WaitPrompt (char*,char*) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MountDVD () ; 
 scalar_t__ NO_DISC ; 
 int SYSTEM_GG ; 
 int SYSTEM_MCD ; 
 int SYSTEM_SG ; 
 int SYSTEM_SMS ; 
 size_t TYPE_DVD ; 
 int TYPE_RECENT ; 
 TYPE_8__ cdc ; 
 TYPE_7__ cdd ; 
 int cdd_load (char*,char*) ; 
 TYPE_6__ config ; 
 int deviceType ; 
 char* fileDir ; 
 TYPE_5__* filelist ; 
 int /*<<< orphan*/  getrominfo (char*) ; 
 TYPE_4__ history ; 
 int /*<<< orphan*/  history_add_file (char*,char*,int) ; 
 int load_rom (char*) ; 
 char* rom_filename ; 
 int romtype ; 
 char** rootdir ; 
 TYPE_3__ scd ; 
 int /*<<< orphan*/  slot_autosave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int system_hw ; 

int LoadFile(int selection) 
{
  int size, cd_mode1, filetype;
  char filename[MAXPATHLEN];

  /* file path */
  char *filepath = (deviceType == TYPE_RECENT) ? history.entries[selection].filepath : fileDir;

  /* full filename */
  sprintf(filename, "%s%s", filepath, filelist[selection].filename);

  /* DVD hot swap  */
  if (!strncmp(filepath, rootdir[TYPE_DVD], strlen(rootdir[TYPE_DVD])))
  {
    /* Check if file is still accessible */
    struct stat filestat;
    if(stat(filename, &filestat) != 0)
    {
      /* If not, try to mount DVD */
      if (!MountDVD()) return 0;
    }
  }

  /* open message box */
  GUI_MsgBoxOpen("Information", "Loading game...", 1);

  /* no cartridge or CD game loaded */
  size = cd_mode1 = 0;

  /* check if virtual CD tray was open */
  if ((system_hw == SYSTEM_MCD) && (cdd.status == CD_OPEN))
  {
    /* swap CD image file in (without changing region, system,...) */
    size = cdd_load(filename, (char *)(cdc.ram));

    /* check if a cartridge is currently loaded  */
    if (scd.cartridge.boot)
    {
      /* CD Mode 1 */
      cd_mode1 = size;
    }
    else
    {
      /* update game informations from CD image file header */
      getrominfo((char *)(cdc.ram));
    }
  }

  /* no CD image file loaded */
  if (!size)
  {
    /* close CD tray to force system reset */
    cdd.status = NO_DISC;

    /* load game file */
    size = load_rom(filename);
  }

  if (size > 0)
  {
    /* do not update game basename if a CD was loaded with a cartridge (Mode 1) */
    if (cd_mode1)
    {
      /* add CD image file to history list */
      filetype = 1;
    }
    else
    {
      /* auto-save previous game state */
      slot_autosave(config.s_default,config.s_device);

      /* update game basename (for screenshot, save & cheat files) */
      if (romtype & SYSTEM_SMS)
      {
        /* Master System ROM file */
        filetype = 2;
        sprintf(rom_filename,"ms/%s",filelist[selection].filename);
      }
      else if (romtype & SYSTEM_GG)
      {
        /* Game Gear ROM file */
        filetype = 3;
        sprintf(rom_filename,"gg/%s",filelist[selection].filename);
      }
      else if (romtype == SYSTEM_SG)
      {
        /* SG-1000 ROM file */
        filetype = 4;
        sprintf(rom_filename,"sg/%s",filelist[selection].filename);
      }
      else if (romtype == SYSTEM_MCD)
      {
        /* CD image file */
        filetype = 1;
        sprintf(rom_filename,"cd/%s",filelist[selection].filename);
      }
      else
      {
        /* by default, Genesis ROM file */
        filetype = 0;
        sprintf(rom_filename,"md/%s",filelist[selection].filename);
      }

      /* remove file extension */
      int i = strlen(rom_filename) - 1;
      while ((i > 0) && (rom_filename[i] != '.')) i--;
      if (i > 0) rom_filename[i] = 0;
    }

    /* add/move the file to the top of the history. */
    history_add_file(filepath, filelist[selection].filename, filetype);

    /* recent file list may have changed */
    if (deviceType == TYPE_RECENT) deviceType = -1;

    /* close message box */
    GUI_MsgBoxClose();

    /* valid image has been loaded */
    return 1;
  }

  GUI_WaitPrompt("Error", "Unable to load game");
  return 0;
}