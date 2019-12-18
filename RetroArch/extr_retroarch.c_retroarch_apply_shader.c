#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  video_shader_enable; } ;
struct TYPE_9__ {TYPE_2__ bools; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;
struct TYPE_7__ {char* library_name; } ;
struct TYPE_10__ {TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_ERROR ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_APPLYING_SHADER ; 
 int /*<<< orphan*/  MSG_FAILED_TO_APPLY_SHADER_PRESET ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  configuration_set_bool (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* configuration_settings ; 
 int /*<<< orphan*/  fill_pathname_join_delim (char*,int /*<<< orphan*/ ,char const*,char,int) ; 
 int /*<<< orphan*/  menu_shader_get () ; 
 scalar_t__ menu_shader_manager_set_preset (int /*<<< orphan*/ ,int,char const*,int) ; 
 int /*<<< orphan*/  menu_shader_set_modified (int) ; 
 scalar_t__ menu_widgets_inited ; 
 int /*<<< orphan*/  menu_widgets_set_message (char*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char const*) ; 
 int /*<<< orphan*/  retroarch_set_runtime_shader_preset (char const*) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ runloop_system ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int video_driver_set_shader (int,char const*) ; 

bool retroarch_apply_shader(enum rarch_shader_type type, const char *preset_path, bool message)
{
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
   settings_t *settings  = configuration_settings;
   const char *core_name = runloop_system.info.library_name;
   bool ret;
   char msg[256];
   const char *preset_file = NULL;

   /* disallow loading shaders when no core is loaded */
   if (string_is_empty(core_name))
      return false;

   if (!string_is_empty(preset_path))
      preset_file = path_basename(preset_path);

   ret = video_driver_set_shader(type, preset_path);

   if (ret)
   {
      configuration_set_bool(settings, settings->bools.video_shader_enable, true);
      retroarch_set_runtime_shader_preset(preset_path);

#ifdef HAVE_MENU
      /* reflect in shader manager */
      if (menu_shader_manager_set_preset(menu_shader_get(), type, preset_path, false))
         if (!string_is_empty(preset_path))
            menu_shader_set_modified(false);
#endif

      if (message)
      {
         /* Display message */
         snprintf(msg, sizeof(msg),
               preset_file ? "Shader: \"%s\"" : "Shader: %s",
               preset_file ? preset_file : "None");
#ifdef HAVE_MENU_WIDGETS
         if (menu_widgets_inited)
            menu_widgets_set_message(msg);
         else
#endif
            runloop_msg_queue_push(msg, 1, 120, true, NULL,
                  MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      }

      RARCH_LOG("%s \"%s\".\n",
            msg_hash_to_str(MSG_APPLYING_SHADER),
            preset_path ? preset_path : "null");
   }
   else
   {
      retroarch_set_runtime_shader_preset(NULL);

#ifdef HAVE_MENU
      /* reflect in shader manager */
      menu_shader_manager_set_preset(menu_shader_get(), type, NULL, false);
#endif

      /* Display error message */
      fill_pathname_join_delim(msg,
            msg_hash_to_str(MSG_FAILED_TO_APPLY_SHADER_PRESET),
            preset_file ? preset_file : "null",
            ' ',
            sizeof(msg));

      runloop_msg_queue_push(
            msg, 1, 180, true, NULL,
            MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_ERROR);
   }

   return ret;
#else
   return false;
#endif
}