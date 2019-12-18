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
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_GET_TITLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  MENU_SETTINGS 131 
#define  MENU_SETTINGS_CUSTOM_BIND 130 
#define  MENU_SETTINGS_CUSTOM_BIND_KEYBOARD 129 
#define  MENU_SETTING_ACTION_CORE_DISK_OPTIONS 128 
 int /*<<< orphan*/  action_get_title_action_generic ; 
 int /*<<< orphan*/  action_get_title_input_settings ; 
 int /*<<< orphan*/  action_get_title_menu ; 

__attribute__((used)) static int menu_cbs_init_bind_title_compare_type(menu_file_list_cbs_t *cbs,
      unsigned type)
{
   switch (type)
   {
      case MENU_SETTINGS:
         BIND_ACTION_GET_TITLE(cbs, action_get_title_menu);
         break;
      case MENU_SETTINGS_CUSTOM_BIND:
      case MENU_SETTINGS_CUSTOM_BIND_KEYBOARD:
         BIND_ACTION_GET_TITLE(cbs, action_get_title_input_settings);
         break;
      case MENU_SETTING_ACTION_CORE_DISK_OPTIONS:
         BIND_ACTION_GET_TITLE(cbs, action_get_title_action_generic);
         break;
      default:
         return -1;
   }

   return 0;
}