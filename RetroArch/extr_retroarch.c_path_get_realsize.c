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
typedef  int /*<<< orphan*/  subsystem_path ;
typedef  int /*<<< orphan*/  path_main_basename ;
typedef  int /*<<< orphan*/  path_libretro ;
typedef  int /*<<< orphan*/  path_default_shader_preset ;
typedef  int /*<<< orphan*/  path_core_options_file ;
typedef  int /*<<< orphan*/  path_content ;
typedef  int /*<<< orphan*/  path_config_file ;
typedef  int /*<<< orphan*/  path_config_append_file ;
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

size_t path_get_realsize(enum rarch_path_type type)
{
   switch (type)
   {
      case RARCH_PATH_CONTENT:
         return sizeof(path_content);
      case RARCH_PATH_DEFAULT_SHADER_PRESET:
         return sizeof(path_default_shader_preset);
      case RARCH_PATH_BASENAME:
         return sizeof(path_main_basename);
      case RARCH_PATH_CORE_OPTIONS:
         return sizeof(path_core_options_file);
      case RARCH_PATH_SUBSYSTEM:
         return sizeof(subsystem_path);
      case RARCH_PATH_CONFIG:
         return sizeof(path_config_file);
      case RARCH_PATH_CONFIG_APPEND:
         return sizeof(path_config_append_file);
      case RARCH_PATH_CORE:
         return sizeof(path_libretro);
      case RARCH_PATH_NONE:
      case RARCH_PATH_NAMES:
         break;
   }

   return 0;
}