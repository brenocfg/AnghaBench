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
struct video_shader_parameter {int /*<<< orphan*/  current; } ;
struct video_shader {int /*<<< orphan*/  num_parameters; int /*<<< orphan*/  parameters; } ;
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_WARN (char*,char const*) ; 
 int /*<<< orphan*/  config_get_array (int /*<<< orphan*/ *,char*,char*,size_t) ; 
 int /*<<< orphan*/  config_get_float (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 char* strtok_r (char*,char*,char**) ; 
 scalar_t__ video_shader_parse_find_parameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

bool video_shader_resolve_current_parameters(config_file_t *conf,
      struct video_shader *shader)
{
   size_t param_size     = 4096 * sizeof(char);
   const char *id        = NULL;
   char *parameters      = NULL;
   char *save            = NULL;

   if (!conf)
      return false;

   parameters            = (char*)malloc(param_size);

   if (!parameters)
      return false;

   parameters[0]         = '\0';

   /* Read in parameters which override the defaults. */
   if (!config_get_array(conf, "parameters",
            parameters, param_size))
   {
      free(parameters);
      return true;
   }

   for (id = strtok_r(parameters, ";", &save); id;
         id = strtok_r(NULL, ";", &save))
   {
      struct video_shader_parameter *parameter =
         (struct video_shader_parameter*)
         video_shader_parse_find_parameter(
               shader->parameters, shader->num_parameters, id);

      if (!parameter)
      {
         RARCH_WARN("[CGP/GLSLP]: Parameter %s is set in the preset,"
               " but no shader uses this parameter, ignoring.\n", id);
         continue;
      }

      if (!config_get_float(conf, id, &parameter->current))
         RARCH_WARN("[CGP/GLSLP]: Parameter %s is not set in preset.\n", id);
   }

   free(parameters);
   return true;
}