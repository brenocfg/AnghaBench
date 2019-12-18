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
typedef  enum rarch_path_type { ____Placeholder_rarch_path_type } rarch_path_type ;

/* Variables and functions */
#define  RARCH_PATH_BASENAME 137 
#define  RARCH_PATH_CONFIG 136 
#define  RARCH_PATH_CONFIG_APPEND 135 
#define  RARCH_PATH_CONTENT 134 
#define  RARCH_PATH_CORE 133 
#define  RARCH_PATH_CORE_OPTIONS 132 
#define  RARCH_PATH_DEFAULT_SHADER_PRESET 131 
#define  RARCH_PATH_NAMES 130 
#define  RARCH_PATH_NONE 129 
#define  RARCH_PATH_SUBSYSTEM 128 
 int /*<<< orphan*/  path_config_append_file ; 
 int /*<<< orphan*/  path_config_file ; 
 int /*<<< orphan*/  path_content ; 
 int /*<<< orphan*/  path_core_options_file ; 
 int /*<<< orphan*/  path_default_shader_preset ; 
 int /*<<< orphan*/  path_libretro ; 
 int /*<<< orphan*/  path_main_basename ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subsystem_path ; 

bool path_is_empty(enum rarch_path_type type)
{
   switch (type)
   {
      case RARCH_PATH_DEFAULT_SHADER_PRESET:
         if (string_is_empty(path_default_shader_preset))
            return true;
         break;
      case RARCH_PATH_SUBSYSTEM:
         if (string_is_empty(subsystem_path))
            return true;
         break;
      case RARCH_PATH_CONFIG:
         if (string_is_empty(path_config_file))
            return true;
         break;
      case RARCH_PATH_CORE_OPTIONS:
         if (string_is_empty(path_core_options_file))
            return true;
         break;
      case RARCH_PATH_CONFIG_APPEND:
         if (string_is_empty(path_config_append_file))
            return true;
         break;
      case RARCH_PATH_CONTENT:
         if (string_is_empty(path_content))
            return true;
         break;
      case RARCH_PATH_CORE:
         if (string_is_empty(path_libretro))
            return true;
         break;
      case RARCH_PATH_BASENAME:
         if (string_is_empty(path_main_basename))
            return true;
         break;
      case RARCH_PATH_NONE:
      case RARCH_PATH_NAMES:
         break;
   }

   return false;
}