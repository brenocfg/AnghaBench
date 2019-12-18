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
 char* path_config_append_file ; 
 char* path_config_file ; 
 char* path_content ; 
 char* path_core_options_file ; 
 char* path_default_shader_preset ; 
 char* path_libretro ; 
 char* path_main_basename ; 
 char* subsystem_path ; 

void path_clear(enum rarch_path_type type)
{
   switch (type)
   {
      case RARCH_PATH_SUBSYSTEM:
         *subsystem_path = '\0';
         break;
      case RARCH_PATH_CORE:
         *path_libretro = '\0';
         break;
      case RARCH_PATH_CONFIG:
         *path_config_file = '\0';
         break;
      case RARCH_PATH_CONTENT:
         *path_content = '\0';
         break;
      case RARCH_PATH_BASENAME:
         *path_main_basename = '\0';
         break;
      case RARCH_PATH_CORE_OPTIONS:
         *path_core_options_file = '\0';
         break;
      case RARCH_PATH_DEFAULT_SHADER_PRESET:
         *path_default_shader_preset = '\0';
         break;
      case RARCH_PATH_CONFIG_APPEND:
         *path_config_append_file = '\0';
         break;
      case RARCH_PATH_NONE:
      case RARCH_PATH_NAMES:
         break;
   }
}