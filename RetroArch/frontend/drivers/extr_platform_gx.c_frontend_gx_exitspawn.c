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
typedef  int /*<<< orphan*/  salamander_name ;
typedef  int /*<<< orphan*/  salamander_basename ;
typedef  int /*<<< orphan*/  new_path ;
struct TYPE_2__ {int /*<<< orphan*/ * dirs; } ;

/* Variables and functions */
 size_t DEFAULT_DIR_CORE ; 
#define  FRONTEND_FORK_CORE 131 
#define  FRONTEND_FORK_CORE_WITH_ARGS 130 
#define  FRONTEND_FORK_NONE 129 
#define  FRONTEND_FORK_RESTART 128 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  fill_pathname_join (char*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  frontend_driver_get_salamander_basename (char*,int) ; 
 int /*<<< orphan*/  frontend_gx_exec (char*,int) ; 
 TYPE_1__ g_defaults ; 
 int gx_fork_mode ; 
 int /*<<< orphan*/  gx_rom_path ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void frontend_gx_exitspawn(char *s, size_t len)
{
   bool should_load_game = false;
#if defined(IS_SALAMANDER)
   if (!string_is_empty(gx_rom_path))
      should_load_game = true;
#elif defined(HW_RVL)
   char salamander_basename[PATH_MAX_LENGTH];

   if (gx_fork_mode == FRONTEND_FORK_NONE)
      return;

   switch (gx_fork_mode)
   {
      case FRONTEND_FORK_CORE_WITH_ARGS:
         should_load_game = true;
         break;
      case FRONTEND_FORK_CORE:
         /* fall-through */
      case FRONTEND_FORK_RESTART:
         {
            char new_path[PATH_MAX_LENGTH];
            char salamander_name[PATH_MAX_LENGTH];

            if (frontend_driver_get_salamander_basename(salamander_name,
                     sizeof(salamander_name)))
            {
               fill_pathname_join(new_path, g_defaults.dirs[DEFAULT_DIR_CORE],
                     salamander_name, sizeof(new_path));
               path_set(RARCH_PATH_CONTENT, new_path);
            }
         }
         break;
      case FRONTEND_FORK_NONE:
      default:
         break;
   }

   frontend_gx_exec(s, should_load_game);
   frontend_driver_get_salamander_basename(salamander_basename,
         sizeof(salamander_basename));

   /* FIXME/TODO - hack
    * direct loading failed (out of memory),
    * try to jump to Salamander,
    * then load the correct core */
   fill_pathname_join(s, g_defaults.dirs[DEFAULT_DIR_CORE],
         salamander_basename, len);
#endif
   frontend_gx_exec(s, should_load_game);
}