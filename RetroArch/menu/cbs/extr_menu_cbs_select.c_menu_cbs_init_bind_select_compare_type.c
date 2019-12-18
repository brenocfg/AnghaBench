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
 int /*<<< orphan*/  BIND_ACTION_SELECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  FILE_TYPE_USE_DIRECTORY 128 
 unsigned int MENU_SETTINGS_CHEAT_BEGIN ; 
 unsigned int MENU_SETTINGS_CHEAT_END ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_BEGIN ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_END ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_KBD_BEGIN ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_KBD_END ; 
 unsigned int MENU_SETTINGS_SHADER_PARAMETER_0 ; 
 unsigned int MENU_SETTINGS_SHADER_PARAMETER_LAST ; 
 unsigned int MENU_SETTINGS_SHADER_PRESET_PARAMETER_0 ; 
 unsigned int MENU_SETTINGS_SHADER_PRESET_PARAMETER_LAST ; 
 int /*<<< orphan*/  action_select_cheat ; 
 int /*<<< orphan*/  action_select_input_desc ; 
 int /*<<< orphan*/  action_select_input_desc_kbd ; 
 int /*<<< orphan*/  action_select_path_use_directory ; 
 int /*<<< orphan*/  shader_action_parameter_preset_select ; 
 int /*<<< orphan*/  shader_action_parameter_select ; 

__attribute__((used)) static int menu_cbs_init_bind_select_compare_type(
      menu_file_list_cbs_t *cbs, unsigned type)
{
   if (type >= MENU_SETTINGS_CHEAT_BEGIN
         && type <= MENU_SETTINGS_CHEAT_END)
   {
      BIND_ACTION_SELECT(cbs, action_select_cheat);
   }
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
   else if (type >= MENU_SETTINGS_SHADER_PARAMETER_0
         && type <= MENU_SETTINGS_SHADER_PARAMETER_LAST)
   {
      BIND_ACTION_SELECT(cbs, shader_action_parameter_select);
   }
   else if (type >= MENU_SETTINGS_SHADER_PRESET_PARAMETER_0
         && type <= MENU_SETTINGS_SHADER_PRESET_PARAMETER_LAST)
   {
      BIND_ACTION_SELECT(cbs, shader_action_parameter_preset_select);
   }
#endif
   else if (type >= MENU_SETTINGS_INPUT_DESC_BEGIN
         && type <= MENU_SETTINGS_INPUT_DESC_END)
   {
      BIND_ACTION_SELECT(cbs, action_select_input_desc);
   }
   else if (type >= MENU_SETTINGS_INPUT_DESC_KBD_BEGIN
         && type <= MENU_SETTINGS_INPUT_DESC_KBD_END)
   {
      BIND_ACTION_SELECT(cbs, action_select_input_desc_kbd);
   }
   else
   {

      switch (type)
      {
         case FILE_TYPE_USE_DIRECTORY:
            BIND_ACTION_SELECT(cbs, action_select_path_use_directory);
            break;
         default:
            return -1;
      }
   }

   return 0;
}