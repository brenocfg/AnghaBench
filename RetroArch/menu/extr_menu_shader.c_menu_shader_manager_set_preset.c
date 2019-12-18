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
struct video_shader {int dummy; } ;
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_SHADER_PRESET_LOADED ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  menu_shader_manager_clear_num_passes (struct video_shader*) ; 
 int /*<<< orphan*/  retroarch_apply_shader (int,char const*,int) ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ video_shader_read_conf_preset (int /*<<< orphan*/ *,struct video_shader*) ; 
 int /*<<< orphan*/ * video_shader_read_preset (char const*) ; 
 int /*<<< orphan*/  video_shader_resolve_parameters (int /*<<< orphan*/ *,struct video_shader*) ; 

bool menu_shader_manager_set_preset(struct video_shader *shader,
      enum rarch_shader_type type, const char *preset_path, bool apply)
{
   config_file_t *conf           = NULL;
   bool refresh                  = false;
   bool ret                      = false;

   if (apply && !retroarch_apply_shader(type, preset_path, true))
   {
      /* We don't want to disable shaders entirely here,
       * just reset number of passes
       * > Note: Disabling shaders at this point would in
       *   fact be dangerous, since it changes the number of
       *   entries in the shader options menu which can in
       *   turn lead to the menu selection pointer going out
       *   of bounds. This causes undefined behaviour/segfaults */
      menu_shader_manager_clear_num_passes(shader);
      command_event(CMD_EVENT_SHADER_PRESET_LOADED, NULL);
      return false;
   }

   if (string_is_empty(preset_path))
   {
      menu_shader_manager_clear_num_passes(shader);
      command_event(CMD_EVENT_SHADER_PRESET_LOADED, NULL);
      return true;
   }

   if (!shader)
   {
      ret = false;
      goto end;
   }

   /* Load stored Preset into menu on success.
    * Used when a preset is directly loaded.
    * No point in updating when the Preset was
    * created from the menu itself. */
   if (!(conf = video_shader_read_preset(preset_path)))
   {
      ret = false;
      goto end;
   }

   RARCH_LOG("Setting Menu shader: %s.\n", preset_path);

   if (video_shader_read_conf_preset(conf, shader))
      video_shader_resolve_parameters(conf, shader);

   if (conf)
      config_file_free(conf);

   ret = true;

end:
   command_event(CMD_EVENT_SHADER_PRESET_LOADED, NULL);
#ifdef HAVE_MENU
   menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
#endif
   return ret;
}