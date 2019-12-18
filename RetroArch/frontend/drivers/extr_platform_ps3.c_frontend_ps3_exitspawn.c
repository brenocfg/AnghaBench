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
struct TYPE_3__ {int /*<<< orphan*/  shutdown; } ;
typedef  TYPE_1__ frontend_ctx_driver_t ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_SYSMODULE_FS ; 
 int /*<<< orphan*/  CELL_SYSMODULE_IO ; 
 int /*<<< orphan*/  CELL_SYSMODULE_SYSUTIL_GAME ; 
#define  FRONTEND_FORK_CORE_WITH_ARGS 129 
#define  FRONTEND_FORK_NONE 128 
 int /*<<< orphan*/  cellSysmoduleLoadModule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cellSysmoduleUnloadModule (int /*<<< orphan*/ ) ; 
 TYPE_1__* frontend_get_ptr () ; 
 int /*<<< orphan*/  frontend_ps3_exec (char*,int) ; 
 int /*<<< orphan*/  frontend_ps3_shutdown ; 
 int ps3_fork_mode ; 
 int /*<<< orphan*/  verbosity_disable () ; 
 int /*<<< orphan*/  verbosity_enable () ; 
 int verbosity_is_enabled () ; 

__attribute__((used)) static void frontend_ps3_exitspawn(char *core_path, size_t core_path_size)
{
#ifdef HAVE_RARCH_EXEC
   bool should_load_game = false;

#ifndef IS_SALAMANDER
   bool original_verbose = verbosity_is_enabled();

   verbosity_enable();

   if (ps3_fork_mode == FRONTEND_FORK_NONE)
   {
      frontend_ctx_driver_t *frontend = frontend_get_ptr();

      if (frontend)
         frontend->shutdown = frontend_ps3_shutdown;
      return;
   }

   switch (ps3_fork_mode)
   {
      case FRONTEND_FORK_CORE_WITH_ARGS:
         should_load_game = true;
         break;
      case FRONTEND_FORK_NONE:
      default:
         break;
   }
#endif

   frontend_ps3_exec(core_path, should_load_game);

#ifdef IS_SALAMANDER
   cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_GAME);
   cellSysmoduleLoadModule(CELL_SYSMODULE_FS);
   cellSysmoduleLoadModule(CELL_SYSMODULE_IO);
#endif

#ifndef IS_SALAMANDER
   if (original_verbose)
      verbosity_enable();
   else
      verbosity_disable();
#endif
#endif
}