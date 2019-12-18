#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wrap_mode ;
struct video_shader {size_t luts; TYPE_1__* lut; } ;
typedef  int /*<<< orphan*/  id_wrap ;
typedef  int /*<<< orphan*/  id_mipmap ;
typedef  int /*<<< orphan*/  id_filter ;
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ config_file_t ;
struct TYPE_6__ {char* id; int mipmap; int /*<<< orphan*/  wrap; int /*<<< orphan*/  filter; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 size_t GFX_MAX_TEXTURES ; 
 size_t PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char const*) ; 
 int /*<<< orphan*/  RARCH_FILTER_LINEAR ; 
 int /*<<< orphan*/  RARCH_FILTER_NEAREST ; 
 int /*<<< orphan*/  RARCH_FILTER_UNSPEC ; 
 scalar_t__ config_get_array (TYPE_2__*,char const*,char*,int) ; 
 scalar_t__ config_get_bool (TYPE_2__*,char*,int*) ; 
 int /*<<< orphan*/  fill_pathname_resolve_relative (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  wrap_str_to_mode (char*) ; 

__attribute__((used)) static bool video_shader_parse_textures(config_file_t *conf,
      struct video_shader *shader)
{
   size_t path_size     = PATH_MAX_LENGTH;
   const char *id       = NULL;
   char *save           = NULL;
   char *textures       = (char*)malloc(1024 + path_size);
   char *tmp_path       = textures + 1024;

   if (!textures)
      return false;

   textures[0] = '\0';

   if (!config_get_array(conf, "textures", textures, 1024))
   {
      free(textures);
      return true;
   }

   for (id = strtok_r(textures, ";", &save);
         id && shader->luts < GFX_MAX_TEXTURES;
         shader->luts++, id = strtok_r(NULL, ";", &save))
   {
      char id_filter[64];
      char id_wrap[64];
      char wrap_mode[64];
      char id_mipmap[64];
      bool mipmap         = false;
      bool smooth         = false;

      id_filter[0] = id_wrap[0] = wrap_mode[0] = id_mipmap[0] = '\0';

      if (!config_get_array(conf, id, tmp_path, path_size))
      {
         RARCH_ERR("Cannot find path to texture \"%s\" ...\n", id);
         free(textures);
         return false;
      }

      fill_pathname_resolve_relative(shader->lut[shader->luts].path,
            conf->path, tmp_path, sizeof(shader->lut[shader->luts].path));

      strlcpy(shader->lut[shader->luts].id, id,
            sizeof(shader->lut[shader->luts].id));

      strlcpy(id_filter, id, sizeof(id_filter));
      strlcat(id_filter, "_linear", sizeof(id_filter));
      if (config_get_bool(conf, id_filter, &smooth))
         shader->lut[shader->luts].filter = smooth ?
            RARCH_FILTER_LINEAR : RARCH_FILTER_NEAREST;
      else
         shader->lut[shader->luts].filter = RARCH_FILTER_UNSPEC;

      strlcpy(id_wrap, id, sizeof(id_wrap));
      strlcat(id_wrap, "_wrap_mode", sizeof(id_wrap));
      if (config_get_array(conf, id_wrap, wrap_mode, sizeof(wrap_mode)))
         shader->lut[shader->luts].wrap = wrap_str_to_mode(wrap_mode);

      strlcpy(id_mipmap, id, sizeof(id_mipmap));
      strlcat(id_mipmap, "_mipmap", sizeof(id_mipmap));
      if (config_get_bool(conf, id_mipmap, &mipmap))
         shader->lut[shader->luts].mipmap = mipmap;
      else
         shader->lut[shader->luts].mipmap = false;
   }

   free(textures);
   return true;
}