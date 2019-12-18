#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* path; } ;
struct video_shader_pass {scalar_t__ filter; scalar_t__ frame_count_mod; int mipmap; char* alias; int /*<<< orphan*/  fbo; int /*<<< orphan*/  wrap; TYPE_1__ source; } ;
struct video_shader {scalar_t__ passes; scalar_t__ feedback_pass; int num_parameters; int luts; TYPE_3__* lut; TYPE_2__* parameters; struct video_shader_pass* pass; } ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_6__ {char const* id; char const* path; scalar_t__ filter; int mipmap; int /*<<< orphan*/  wrap; } ;
struct TYPE_5__ {char const* id; int /*<<< orphan*/  current; } ;

/* Variables and functions */
 size_t PATH_MAX_LENGTH ; 
 scalar_t__ RARCH_FILTER_LINEAR ; 
 scalar_t__ RARCH_FILTER_UNSPEC ; 
 int /*<<< orphan*/  config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  config_set_float (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_set_int (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  config_set_path (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  make_relative_path_portable (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  path_basedir (char*) ; 
 int /*<<< orphan*/  path_relative_to (char*,char*,char*,size_t) ; 
 int /*<<< orphan*/  path_resolve_realpath (char*,size_t,int) ; 
 int /*<<< orphan*/  shader_write_fbo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* wrap_mode_to_str (int /*<<< orphan*/ ) ; 

void video_shader_write_conf_preset(config_file_t *conf,
      const struct video_shader *shader, const char *preset_path)
{
   unsigned i;
   char key[64];
   size_t tmp_size = PATH_MAX_LENGTH;
   char *tmp       = (char*)malloc(3*tmp_size);
   char *tmp_rel   = tmp +   tmp_size;
   char *tmp_base  = tmp + 2*tmp_size;

   if (!tmp)
      return;

   config_set_int(conf, "shaders", shader->passes);
   if (shader->feedback_pass >= 0)
      config_set_int(conf, "feedback_pass", shader->feedback_pass);

   if (preset_path)
   {
      strlcpy(tmp_base, preset_path, tmp_size);

      /* ensure we use a clean base like the shader passes and texture paths do */
      path_resolve_realpath(tmp_base, tmp_size, false);
      path_basedir(tmp_base);
   }

   for (i = 0; i < shader->passes; i++)
   {
      const struct video_shader_pass *pass = &shader->pass[i];

      snprintf(key, sizeof(key), "shader%u", i);

      if (preset_path)
      {
         strlcpy(tmp, pass->source.path, tmp_size);
         path_relative_to(tmp_rel, tmp, tmp_base, tmp_size);
         make_relative_path_portable(tmp_rel);

         config_set_path(conf, key, tmp_rel);
      }
      else
         config_set_path(conf, key, pass->source.path);


      if (pass->filter != RARCH_FILTER_UNSPEC)
      {
         snprintf(key, sizeof(key), "filter_linear%u", i);
         config_set_bool(conf, key, pass->filter == RARCH_FILTER_LINEAR);
      }

      snprintf(key, sizeof(key), "wrap_mode%u", i);
      config_set_string(conf, key, wrap_mode_to_str(pass->wrap));

      if (pass->frame_count_mod)
      {
         snprintf(key, sizeof(key), "frame_count_mod%u", i);
         config_set_int(conf, key, pass->frame_count_mod);
      }

      snprintf(key, sizeof(key), "mipmap_input%u", i);
      config_set_bool(conf, key, pass->mipmap);

      snprintf(key, sizeof(key), "alias%u", i);
      config_set_string(conf, key, pass->alias);

      shader_write_fbo(conf, &pass->fbo, i);
   }


   if (shader->num_parameters)
   {
      size_t param_size = 4096 * sizeof(char);
      char *parameters  = (char*)malloc(param_size);

      if (parameters)
      {
         parameters[0] = '\0';

         strlcpy(parameters, shader->parameters[0].id, param_size);

         for (i = 1; i < shader->num_parameters; i++)
         {
            /* O(n^2), but number of parameters is very limited. */
            strlcat(parameters, ";", param_size);
            strlcat(parameters, shader->parameters[i].id, param_size);
         }

         config_set_string(conf, "parameters", parameters);

         for (i = 0; i < shader->num_parameters; i++)
            config_set_float(conf, shader->parameters[i].id,
                  shader->parameters[i].current);
         free(parameters);
      }
   }

   if (shader->luts)
   {
      size_t tex_size = 4096 * sizeof(char);
      char *textures  = (char*)malloc(tex_size);

      if (textures)
      {
         textures[0] = '\0';

         strlcpy(textures, shader->lut[0].id, tex_size);

         for (i = 1; i < shader->luts; i++)
         {
            /* O(n^2), but number of textures is very limited. */
            strlcat(textures, ";", tex_size);
            strlcat(textures, shader->lut[i].id, tex_size);
         }

         config_set_string(conf, "textures", textures);

         free(textures);

         for (i = 0; i < shader->luts; i++)
         {
            if (preset_path)
            {
               strlcpy(tmp, shader->lut[i].path, tmp_size);
               path_relative_to(tmp_rel, tmp, tmp_base, tmp_size);
               make_relative_path_portable(tmp_rel);

               config_set_path(conf, shader->lut[i].id, tmp_rel);
            }
            else
               config_set_path(conf, shader->lut[i].id, shader->lut[i].path);

            if (shader->lut[i].filter != RARCH_FILTER_UNSPEC)
            {
               char key[128];
               key[0]  = '\0';
               strlcpy(key, shader->lut[i].id, sizeof(key));
               strlcat(key, "_linear", sizeof(key));
               config_set_bool(conf, key,
                     shader->lut[i].filter == RARCH_FILTER_LINEAR);
            }

            {
               char key[128];
               key[0]  = '\0';
               strlcpy(key, shader->lut[i].id, sizeof(key));
               strlcat(key, "_wrap_mode", sizeof(key));
               config_set_string(conf, key,
                     wrap_mode_to_str(shader->lut[i].wrap));
            }

            {
               char key[128];
               key[0]  = '\0';
               strlcpy(key, shader->lut[i].id, sizeof(key));
               strlcat(key, "_mipmap", sizeof(key));
               config_set_bool(conf, key,
                     shader->lut[i].mipmap);
            }
         }
      }
   }

   free(tmp);
}