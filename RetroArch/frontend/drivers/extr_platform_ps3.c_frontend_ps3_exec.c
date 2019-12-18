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
typedef  int /*<<< orphan*/  game_path ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_SYSMODULE_NET ; 
 int /*<<< orphan*/  CELL_SYSMODULE_SYSUTIL_NP ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  cellSysmoduleUnloadModule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frontend_ps3_exec_exitspawn (char const*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceNpTerm () ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sys_net_finalize_network () ; 
 int /*<<< orphan*/  verbosity_disable () ; 
 int /*<<< orphan*/  verbosity_enable () ; 
 int verbosity_is_enabled () ; 

__attribute__((used)) static void frontend_ps3_exec(const char *path, bool should_load_game)
{
#ifndef IS_SALAMANDER
   bool original_verbose = verbosity_is_enabled();
   verbosity_enable();
#endif

   (void)should_load_game;

   RARCH_LOG("Attempt to load executable: [%s].\n", path);

#ifndef IS_SALAMANDER
   if (should_load_game && !path_is_empty(RARCH_PATH_CONTENT))
   {
      char game_path[256];
      strlcpy(game_path, path_get(RARCH_PATH_CONTENT), sizeof(game_path));

      const char * const spawn_argv[] = {
         game_path,
         NULL
      };

      frontend_ps3_exec_exitspawn(path,
            (const char** const)spawn_argv, NULL);
   }
   else
#endif
   {
      frontend_ps3_exec_exitspawn(path,
            NULL, NULL);
   }

   sceNpTerm();
   sys_net_finalize_network();
   cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_NP);
   cellSysmoduleUnloadModule(CELL_SYSMODULE_NET);

#ifndef IS_SALAMANDER
   if (original_verbose)
      verbosity_enable();
   else
      verbosity_disable();
#endif
}