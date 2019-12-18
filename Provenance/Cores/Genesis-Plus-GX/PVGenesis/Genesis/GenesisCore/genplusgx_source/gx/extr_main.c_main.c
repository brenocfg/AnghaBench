#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ autoload; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ ConfigRequested ; 
 char* DEFAULT_PATH ; 
 int /*<<< orphan*/  DI_Init () ; 
 int /*<<< orphan*/  DI_UseCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVD_Init () ; 
 int IOS_GetVersion () ; 
 int /*<<< orphan*/  L2Enhance () ; 
 scalar_t__ LoadFile (int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 scalar_t__ OpenDirectory (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PowerOff_cb ; 
 int /*<<< orphan*/  Reset_cb ; 
 int SILENT ; 
 int /*<<< orphan*/  SYS_SetPowerCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_SetResetCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IRWXU ; 
 int /*<<< orphan*/  TYPE_RECENT ; 
 char* VERSION ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  config_default () ; 
 int fatInitDefault () ; 
 int /*<<< orphan*/  gx_audio_Init () ; 
 int /*<<< orphan*/  gx_audio_Start () ; 
 int /*<<< orphan*/  gx_input_Init () ; 
 int /*<<< orphan*/  gx_video_Init () ; 
 int /*<<< orphan*/  gx_video_Start () ; 
 int /*<<< orphan*/  history_default () ; 
 int /*<<< orphan*/  init_machine () ; 
 int /*<<< orphan*/  legal () ; 
 int /*<<< orphan*/  mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 char* osd_version ; 
 int /*<<< orphan*/  reloadrom () ; 
 int /*<<< orphan*/  run_emulation () ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  usleep (int) ; 

int main (int argc, char *argv[])
{
 #ifdef HW_RVL
  /* enable 64-byte fetch mode for L2 cache */
  L2Enhance();
  
  /* initialize DI interface */
  DI_UseCache(0);
  DI_Init();

  sprintf(osd_version, "%s (IOS %d)", VERSION, IOS_GetVersion());
#else
  sprintf(osd_version, "%s (GCN)", VERSION);
#endif

  /* initialize video engine */
  gx_video_Init();

#ifndef HW_RVL
  /* initialize DVD interface */
  DVD_Init();
#endif

  /* initialize input engine */
  gx_input_Init();

  /* initialize FAT devices */
  int retry = 0;
  int fatMounted = 0;

  /* try to mount FAT devices during 3 seconds */
  while (!fatMounted && (retry < 12))
  {
    fatMounted = fatInitDefault();
    usleep(250000);
    retry++;
  }

  if (fatMounted)
  {
    /* base directory */
    char pathname[MAXPATHLEN];
    sprintf (pathname, DEFAULT_PATH);
    DIR *dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);

    /* default SRAM & Savestate files directories */ 
    sprintf (pathname, "%s/saves",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/saves/md",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/saves/ms",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/saves/gg",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/saves/sg",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/saves/cd",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);

    /* default Snapshot files directories */ 
    sprintf (pathname, "%s/snaps",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/snaps/md",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/snaps/ms",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/snaps/gg",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/snaps/sg",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/snaps/cd",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);

    /* default Cheat files directories */ 
    sprintf (pathname, "%s/cheats",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/cheats/md",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/cheats/ms",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/cheats/gg",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/cheats/sg",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
    sprintf (pathname, "%s/cheats/cd",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);

    /* default BIOS ROM files directories */ 
    sprintf (pathname, "%s/bios",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);

    /* default LOCK-ON ROM files directories */ 
    sprintf (pathname, "%s/lock-on",DEFAULT_PATH);
    dir = opendir(pathname);
    if (dir) closedir(dir);
    else mkdir(pathname,S_IRWXU);
  }

  /* initialize sound engine */
  gx_audio_Init();

  /* initialize genesis plus core */
  history_default();
  config_default();
  init_machine();

  /* auto-load last ROM file */
  if (config.autoload)
  {
    SILENT = 1;
    if (OpenDirectory(TYPE_RECENT, -1))
    {
      if (LoadFile(0))
      {
        reloadrom();
        gx_video_Start();
        gx_audio_Start();
        ConfigRequested = 0;
      }
    }
    SILENT = 0;
  }

  /* show disclaimer */
  if (ConfigRequested)
  {
    legal();
  }

#ifdef HW_RVL
  /* power button callback */
  SYS_SetPowerCallback(PowerOff_cb);
#endif

  /* reset button callback */
  SYS_SetResetCallback(Reset_cb);

  /* main emulation loop */
  run_emulation();

  /* we should never return anyway */
  return 0;
}