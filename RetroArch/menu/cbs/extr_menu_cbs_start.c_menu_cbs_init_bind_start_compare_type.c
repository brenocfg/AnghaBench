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
 int /*<<< orphan*/  BIND_ACTION_START (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MENU_LABEL_SCREEN_RESOLUTION ; 
 unsigned int MENU_SETTINGS_CHEEVOS_START ; 
 unsigned int MENU_SETTINGS_CORE_OPTION_START ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_BEGIN ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_END ; 
 unsigned int MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_BEGIN ; 
 unsigned int MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_END ; 
 unsigned int MENU_SETTINGS_PERF_COUNTERS_BEGIN ; 
 unsigned int MENU_SETTINGS_PERF_COUNTERS_END ; 
 unsigned int MENU_SETTINGS_SHADER_PARAMETER_0 ; 
 unsigned int MENU_SETTINGS_SHADER_PARAMETER_LAST ; 
 unsigned int MENU_SETTINGS_SHADER_PRESET_PARAMETER_0 ; 
 unsigned int MENU_SETTINGS_SHADER_PRESET_PARAMETER_LAST ; 
 int /*<<< orphan*/  action_start_core_setting ; 
 int /*<<< orphan*/  action_start_input_desc ; 
 int /*<<< orphan*/  action_start_performance_counters_core ; 
 int /*<<< orphan*/  action_start_performance_counters_frontend ; 
 int /*<<< orphan*/  action_start_shader_action_parameter ; 
 int /*<<< orphan*/  action_start_video_resolution ; 

__attribute__((used)) static int menu_cbs_init_bind_start_compare_type(menu_file_list_cbs_t *cbs,
      unsigned type)
{
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
   if (type >= MENU_SETTINGS_SHADER_PARAMETER_0
         && type <= MENU_SETTINGS_SHADER_PARAMETER_LAST)
   {
      BIND_ACTION_START(cbs, action_start_shader_action_parameter);
   }
   else if (type >= MENU_SETTINGS_SHADER_PRESET_PARAMETER_0
         && type <= MENU_SETTINGS_SHADER_PRESET_PARAMETER_LAST)
   {
      BIND_ACTION_START(cbs, action_start_shader_action_parameter);
   }
   else
#endif
   if (type >= MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_BEGIN &&
         type <= MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_END)
   {
      BIND_ACTION_START(cbs, action_start_performance_counters_core);
   }
   else if (type >= MENU_SETTINGS_INPUT_DESC_BEGIN
         && type <= MENU_SETTINGS_INPUT_DESC_END)
   {
      BIND_ACTION_START(cbs, action_start_input_desc);
   }
   else if (type >= MENU_SETTINGS_PERF_COUNTERS_BEGIN &&
         type <= MENU_SETTINGS_PERF_COUNTERS_END)
   {
      BIND_ACTION_START(cbs, action_start_performance_counters_frontend);
   }
   else if ((type >= MENU_SETTINGS_CORE_OPTION_START) &&
            (type < MENU_SETTINGS_CHEEVOS_START))
   {
      BIND_ACTION_START(cbs, action_start_core_setting);
   }
   else if (type == MENU_LABEL_SCREEN_RESOLUTION)
   {
      BIND_ACTION_START(cbs, action_start_video_resolution);
   }
   else
      return -1;

   return 0;
}