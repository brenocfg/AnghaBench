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
typedef  int /*<<< orphan*/  retro_task_callback_t ;
typedef  enum rarch_core_type { ____Placeholder_rarch_core_type } rarch_core_type ;
typedef  int /*<<< orphan*/  content_ctx_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PENDING_QUICK_MENU ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retroarch_menu_running () ; 
 int /*<<< orphan*/  retroarch_set_current_core_type (int,int) ; 
 int /*<<< orphan*/  task_load_content_callback (int /*<<< orphan*/ *,int,int) ; 

bool task_push_start_builtin_core(
      content_ctx_info_t *content_info,
      enum rarch_core_type type,
      retro_task_callback_t cb,
      void *user_data)
{
   /* Clear content path */
   path_clear(RARCH_PATH_CONTENT);

   /* Preliminary stuff that has to be done before we
    * load the actual content. Can differ per mode. */
   retroarch_set_current_core_type(type, true);

   /* Load content */
   if (!task_load_content_callback(content_info, true, false))
   {
      retroarch_menu_running();
      return false;
   }

   /* Push quick menu onto menu stack */
#ifdef HAVE_MENU
   menu_driver_ctl(RARCH_MENU_CTL_SET_PENDING_QUICK_MENU, NULL);
#endif

   return true;
}