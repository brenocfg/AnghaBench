#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  retro_task_callback_t ;
struct TYPE_4__ {char* label; } ;
struct TYPE_5__ {TYPE_1__ name; } ;
typedef  TYPE_2__ global_t ;
typedef  int /*<<< orphan*/  content_ctx_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_LOAD_CORE ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PENDING_QUICK_MENU ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 int _launched_from_cli ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* global_get_ptr () ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  task_load_content_callback (int /*<<< orphan*/ *,int,int) ; 

bool task_push_load_content_with_new_core_from_companion_ui(
      const char *core_path,
      const char *fullpath,
      const char *label,
      content_ctx_info_t *content_info,
      retro_task_callback_t cb,
      void *user_data)
{
   global_t *global = global_get_ptr();

   path_set(RARCH_PATH_CONTENT, fullpath);
   path_set(RARCH_PATH_CORE, core_path);
#ifdef HAVE_DYNAMIC
   command_event(CMD_EVENT_LOAD_CORE, NULL);
#endif

   _launched_from_cli = false;

   if (global)
   {
      if (label)
         strlcpy(global->name.label, label, sizeof(global->name.label));
      else
         global->name.label[0] = '\0';
   }

   /* Load content */
   if (!task_load_content_callback(content_info, true, false))
      return false;

#ifdef HAVE_MENU
   /* Push quick menu onto menu stack */
   menu_driver_ctl(RARCH_MENU_CTL_SET_PENDING_QUICK_MENU, NULL);
#endif

   return true;
}