#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ video_shader_ctx_t ;
struct video_shader {int passes; TYPE_3__* pass; } ;
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
struct TYPE_8__ {TYPE_2__ source; } ;
struct TYPE_6__ {char* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_SHADER_PRESET_LOADED ; 
 int RARCH_SHADER_NONE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 struct video_shader* menu_driver_shader ; 
 int menu_driver_shader_modified ; 
 int /*<<< orphan*/  menu_shader_manager_free () ; 
 int /*<<< orphan*/  path_get_extension (char const*) ; 
 char* retroarch_get_shader_preset () ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  video_shader_driver_get_current_shader (TYPE_4__*) ; 
 int video_shader_get_type_from_ext (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  video_shader_is_supported (int) ; 
 scalar_t__ video_shader_read_conf_preset (int /*<<< orphan*/ *,struct video_shader*) ; 
 int /*<<< orphan*/ * video_shader_read_preset (char const*) ; 
 int /*<<< orphan*/  video_shader_resolve_parameters (int /*<<< orphan*/ *,struct video_shader*) ; 

bool menu_shader_manager_init(void)
{
   enum rarch_shader_type type      = RARCH_SHADER_NONE;
   bool ret                         = true;
   bool is_preset                   = false;
   const char *path_shader          = NULL;
   struct video_shader *menu_shader = NULL;

   /* We get the shader preset directly from the video driver, so that
    * we are in sync with it (it could fail loading an auto-shader)
    * If we can't (e.g. get_current_shader is not implemented),
    * we'll load retroarch_get_shader_preset() like always */
   video_shader_ctx_t shader_info = {0};

   video_shader_driver_get_current_shader(&shader_info);

   if (shader_info.data)
      path_shader = shader_info.data->path;
   else
      path_shader = retroarch_get_shader_preset();

   menu_shader_manager_free();

   menu_shader          = (struct video_shader*)
      calloc(1, sizeof(*menu_shader));

   if (!menu_shader)
   {
      ret = false;
      goto end;
   }

   if (string_is_empty(path_shader))
      goto end;

   type = video_shader_get_type_from_ext(path_get_extension(path_shader),
         &is_preset);

   if (!video_shader_is_supported(type))
   {
      ret = false;
      goto end;
   }

   if (is_preset)
   {
      config_file_t *conf = NULL;

      conf = video_shader_read_preset(path_shader);

      if (!conf)
      {
         ret = false;
         goto end;
      }

      if (video_shader_read_conf_preset(conf, menu_shader))
         video_shader_resolve_parameters(conf, menu_shader);

      menu_driver_shader_modified = false;

      config_file_free(conf);
   }
   else
   {
      strlcpy(menu_shader->pass[0].source.path, path_shader,
            sizeof(menu_shader->pass[0].source.path));
      menu_shader->passes = 1;
   }

end:
   menu_driver_shader = menu_shader;
   command_event(CMD_EVENT_SHADER_PRESET_LOADED, NULL);
   return ret;
}