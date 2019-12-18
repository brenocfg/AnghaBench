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
 int /*<<< orphan*/  CELL_SYSMODULE_AVCONF_EXT ; 
 int /*<<< orphan*/  CELL_SYSMODULE_FONT ; 
 int /*<<< orphan*/  CELL_SYSMODULE_FONTFT ; 
 int /*<<< orphan*/  CELL_SYSMODULE_FREETYPE ; 
 int /*<<< orphan*/  CELL_SYSMODULE_JPGDEC ; 
 int /*<<< orphan*/  CELL_SYSMODULE_PNGDEC ; 
 int /*<<< orphan*/  CELL_SYSMODULE_SYSUTIL_GAME ; 
 int /*<<< orphan*/  CELL_SYSMODULE_SYSUTIL_SCREENSHOT ; 
 int /*<<< orphan*/  cellSysmoduleLoadModule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cellSysmoduleUnloadModule (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void frontend_ps3_deinit(void *data)
{
   (void)data;
#ifndef IS_SALAMANDER

#if defined(HAVE_SYSMODULES)
#ifdef HAVE_FREETYPE
   /* Freetype font PRX */
   cellSysmoduleLoadModule(CELL_SYSMODULE_FONTFT);
   cellSysmoduleUnloadModule(CELL_SYSMODULE_FREETYPE);
   cellSysmoduleUnloadModule(CELL_SYSMODULE_FONT);
#endif

#ifndef __PSL1GHT__
   /* screenshot PRX */
   cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_SCREENSHOT);
#endif

   cellSysmoduleUnloadModule(CELL_SYSMODULE_JPGDEC);
   cellSysmoduleUnloadModule(CELL_SYSMODULE_PNGDEC);

#ifndef __PSL1GHT__
   /* system game utility PRX */
   cellSysmoduleUnloadModule(CELL_SYSMODULE_AVCONF_EXT);
   cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_GAME);
#endif

#endif

#endif
}