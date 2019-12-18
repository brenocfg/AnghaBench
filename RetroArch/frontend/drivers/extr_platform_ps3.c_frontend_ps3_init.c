#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* photo_title; char* game_title; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ CellScreenShotSetParam ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_SYSMODULE_AVCONF_EXT ; 
 int /*<<< orphan*/  CELL_SYSMODULE_FONT ; 
 int /*<<< orphan*/  CELL_SYSMODULE_FONTFT ; 
 int /*<<< orphan*/  CELL_SYSMODULE_FREETYPE ; 
 int /*<<< orphan*/  CELL_SYSMODULE_FS ; 
 int /*<<< orphan*/  CELL_SYSMODULE_IO ; 
 int /*<<< orphan*/  CELL_SYSMODULE_JPGDEC ; 
 int /*<<< orphan*/  CELL_SYSMODULE_NET ; 
 int /*<<< orphan*/  CELL_SYSMODULE_PNGDEC ; 
 int /*<<< orphan*/  CELL_SYSMODULE_SYSUTIL_GAME ; 
 int /*<<< orphan*/  CELL_SYSMODULE_SYSUTIL_NP ; 
 int /*<<< orphan*/  CELL_SYSMODULE_SYSUTIL_SCREENSHOT ; 
 int /*<<< orphan*/  NP_POOL_SIZE ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  callback_sysutil_exit ; 
 int /*<<< orphan*/  cellScreenShotEnable () ; 
 int /*<<< orphan*/  cellScreenShotSetParameter (TYPE_1__*) ; 
 int /*<<< orphan*/  cellSysmoduleLoadModule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cellSysutilRegisterCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  np_pool ; 
 int /*<<< orphan*/  sceNpInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_net_initialize_network () ; 

__attribute__((used)) static void frontend_ps3_init(void *data)
{
   (void)data;
#ifdef HAVE_SYSUTILS
   RARCH_LOG("Registering system utility callback...\n");
   cellSysutilRegisterCallback(0, callback_sysutil_exit, NULL);
#endif

#ifdef HAVE_SYSMODULES

#ifdef HAVE_FREETYPE
   cellSysmoduleLoadModule(CELL_SYSMODULE_FONT);
   cellSysmoduleLoadModule(CELL_SYSMODULE_FREETYPE);
   cellSysmoduleLoadModule(CELL_SYSMODULE_FONTFT);
#endif

   cellSysmoduleLoadModule(CELL_SYSMODULE_IO);
   cellSysmoduleLoadModule(CELL_SYSMODULE_FS);
#ifndef __PSL1GHT__
   cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL_GAME);
#endif
#ifndef IS_SALAMANDER
#ifndef __PSL1GHT__
   cellSysmoduleLoadModule(CELL_SYSMODULE_AVCONF_EXT);
#endif
   cellSysmoduleLoadModule(CELL_SYSMODULE_PNGDEC);
   cellSysmoduleLoadModule(CELL_SYSMODULE_JPGDEC);
#endif
   cellSysmoduleLoadModule(CELL_SYSMODULE_NET);
   cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL_NP);
#endif

#ifndef __PSL1GHT__
   sys_net_initialize_network();
   sceNpInit(NP_POOL_SIZE, np_pool);
#endif

#ifndef IS_SALAMANDER
#if (CELL_SDK_VERSION > 0x340000) && !defined(__PSL1GHT__)
#ifdef HAVE_SYSMODULES
   cellSysmoduleLoadModule(CELL_SYSMODULE_SYSUTIL_SCREENSHOT);
#endif
#ifdef HAVE_SYSUTILS
   CellScreenShotSetParam screenshot_param = {0, 0, 0, 0};

   screenshot_param.photo_title = "RetroArch PS3";
   screenshot_param.game_title = "RetroArch PS3";
   cellScreenShotSetParameter (&screenshot_param);
   cellScreenShotEnable();
#endif
#endif
#endif
}