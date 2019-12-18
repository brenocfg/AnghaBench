#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wrap_name_buf ;
typedef  int /*<<< orphan*/  wrap_mode ;
struct gfx_fbo_scale {int srgb_fbo; int fp_fbo; int valid; scalar_t__ type_x; scalar_t__ type_y; double scale_x; double scale_y; int abs_x; int abs_y; } ;
struct TYPE_9__ {int /*<<< orphan*/  path; } ;
struct video_shader_pass {unsigned int frame_count_mod; int mipmap; char* alias; struct gfx_fbo_scale fbo; int /*<<< orphan*/  wrap; int /*<<< orphan*/  filter; TYPE_1__ source; } ;
typedef  int /*<<< orphan*/  srgb_output_buf ;
typedef  int /*<<< orphan*/  shader_name ;
typedef  int /*<<< orphan*/  scale_type_y ;
typedef  int /*<<< orphan*/  scale_type_x ;
typedef  int /*<<< orphan*/  scale_type ;
typedef  int /*<<< orphan*/  scale_name_buf ;
typedef  int /*<<< orphan*/  mipmap_buf ;
typedef  int /*<<< orphan*/  frame_count_mod_buf ;
typedef  int /*<<< orphan*/  frame_count_mod ;
typedef  int /*<<< orphan*/  fp_fbo_buf ;
typedef  int /*<<< orphan*/  filter_name_buf ;
struct TYPE_10__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ config_file_t ;
typedef  int /*<<< orphan*/  attr_name_buf ;
typedef  int /*<<< orphan*/  alias_buf ;

/* Variables and functions */
 size_t PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  RARCH_FILTER_LINEAR ; 
 int /*<<< orphan*/  RARCH_FILTER_NEAREST ; 
 int /*<<< orphan*/  RARCH_FILTER_UNSPEC ; 
 scalar_t__ RARCH_SCALE_ABSOLUTE ; 
 void* RARCH_SCALE_INPUT ; 
 void* RARCH_SCALE_VIEWPORT ; 
 scalar_t__ config_get_array (TYPE_2__*,char*,char*,int) ; 
 scalar_t__ config_get_bool (TYPE_2__*,char*,int*) ; 
 scalar_t__ config_get_float (TYPE_2__*,char*,float*) ; 
 scalar_t__ config_get_int (TYPE_2__*,char*,int*) ; 
 int /*<<< orphan*/  config_get_path (TYPE_2__*,char*,char*,size_t) ; 
 int /*<<< orphan*/  fill_pathname_resolve_relative (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_str_to_mode (char*) ; 

__attribute__((used)) static bool video_shader_parse_pass(config_file_t *conf,
      struct video_shader_pass *pass, unsigned i)
{
   char shader_name[64];
   char filter_name_buf[64];
   char wrap_name_buf[64];
   char wrap_mode[64];
   char frame_count_mod_buf[64];
   char srgb_output_buf[64];
   char fp_fbo_buf[64];
   char mipmap_buf[64];
   char alias_buf[64];
   char scale_name_buf[64];
   char attr_name_buf[64];
   char scale_type[64];
   char scale_type_x[64];
   char scale_type_y[64];
   char frame_count_mod[64];
   size_t path_size             = PATH_MAX_LENGTH;
   char *tmp_path               = (char*)malloc(path_size);
   struct gfx_fbo_scale *scale  = NULL;
   bool tmp_bool                = false;
   float fattr                  = 0.0f;
   int iattr                    = 0;

   if (!tmp_path)
      return false;

   fp_fbo_buf[0]      = mipmap_buf[0]          = alias_buf[0]       =
   scale_name_buf[0]  = attr_name_buf[0]       = scale_type[0]      =
   scale_type_x[0]    = scale_type_y[0]        = frame_count_mod[0] =
   shader_name[0]     = filter_name_buf[0]     = wrap_name_buf[0]   = 
   wrap_mode[0]       = frame_count_mod_buf[0] = srgb_output_buf[0] = '\0';

   /* Source */
   snprintf(shader_name, sizeof(shader_name), "shader%u", i);
   if (!config_get_path(conf, shader_name, tmp_path, path_size))
   {
      RARCH_ERR("Couldn't parse shader source (%s).\n", shader_name);
      free(tmp_path);
      return false;
   }

   fill_pathname_resolve_relative(pass->source.path,
         conf->path, tmp_path, sizeof(pass->source.path));
   free(tmp_path);

   /* Smooth */
   snprintf(filter_name_buf, sizeof(filter_name_buf), "filter_linear%u", i);

   if (config_get_bool(conf, filter_name_buf, &tmp_bool))
   {
      bool smooth = tmp_bool;
      pass->filter = smooth ? RARCH_FILTER_LINEAR : RARCH_FILTER_NEAREST;
   }
   else
      pass->filter = RARCH_FILTER_UNSPEC;

   /* Wrapping mode */
   snprintf(wrap_name_buf, sizeof(wrap_name_buf), "wrap_mode%u", i);
   if (config_get_array(conf, wrap_name_buf, wrap_mode, sizeof(wrap_mode)))
      pass->wrap = wrap_str_to_mode(wrap_mode);

   /* Frame count mod */
   snprintf(frame_count_mod_buf, sizeof(frame_count_mod_buf), "frame_count_mod%u", i);
   if (config_get_array(conf, frame_count_mod_buf,
            frame_count_mod, sizeof(frame_count_mod)))
      pass->frame_count_mod = (unsigned)strtoul(frame_count_mod, NULL, 0);

   /* FBO types and mipmapping */
   snprintf(srgb_output_buf, sizeof(srgb_output_buf), "srgb_framebuffer%u", i);
   if (config_get_bool(conf, srgb_output_buf, &tmp_bool))
      pass->fbo.srgb_fbo = tmp_bool;

   snprintf(fp_fbo_buf, sizeof(fp_fbo_buf), "float_framebuffer%u", i);
   if (config_get_bool(conf, fp_fbo_buf, &tmp_bool))
      pass->fbo.fp_fbo = tmp_bool;

   snprintf(mipmap_buf, sizeof(mipmap_buf), "mipmap_input%u", i);
   if (config_get_bool(conf, mipmap_buf, &tmp_bool))
      pass->mipmap = tmp_bool;

   snprintf(alias_buf, sizeof(alias_buf), "alias%u", i);
   if (!config_get_array(conf, alias_buf, pass->alias, sizeof(pass->alias)))
      *pass->alias = '\0';

   /* Scale */
   scale = &pass->fbo;
   snprintf(scale_name_buf, sizeof(scale_name_buf), "scale_type%u", i);
   config_get_array(conf, scale_name_buf, scale_type, sizeof(scale_type));

   snprintf(scale_name_buf, sizeof(scale_name_buf), "scale_type_x%u", i);
   config_get_array(conf, scale_name_buf, scale_type_x, sizeof(scale_type_x));

   snprintf(scale_name_buf, sizeof(scale_name_buf), "scale_type_y%u", i);
   config_get_array(conf, scale_name_buf, scale_type_y, sizeof(scale_type_y));

   if (!*scale_type && !*scale_type_x && !*scale_type_y)
      return true;

   if (*scale_type)
   {
      strlcpy(scale_type_x, scale_type, sizeof(scale_type_x));
      strlcpy(scale_type_y, scale_type, sizeof(scale_type_y));
   }

   scale->valid   = true;
   scale->type_x  = RARCH_SCALE_INPUT;
   scale->type_y  = RARCH_SCALE_INPUT;
   scale->scale_x = 1.0;
   scale->scale_y = 1.0;

   if (*scale_type_x)
   {
      if (string_is_equal(scale_type_x, "source"))
         scale->type_x = RARCH_SCALE_INPUT;
      else if (string_is_equal(scale_type_x, "viewport"))
         scale->type_x = RARCH_SCALE_VIEWPORT;
      else if (string_is_equal(scale_type_x, "absolute"))
         scale->type_x = RARCH_SCALE_ABSOLUTE;
      else
      {
         RARCH_ERR("Invalid attribute.\n");
         return false;
      }
   }

   if (*scale_type_y)
   {
      if (string_is_equal(scale_type_y, "source"))
         scale->type_y = RARCH_SCALE_INPUT;
      else if (string_is_equal(scale_type_y, "viewport"))
         scale->type_y = RARCH_SCALE_VIEWPORT;
      else if (string_is_equal(scale_type_y, "absolute"))
         scale->type_y = RARCH_SCALE_ABSOLUTE;
      else
      {
         RARCH_ERR("Invalid attribute.\n");
         return false;
      }
   }

   snprintf(attr_name_buf, sizeof(attr_name_buf), "scale%u", i);

   if (scale->type_x == RARCH_SCALE_ABSOLUTE)
   {
      if (config_get_int(conf, attr_name_buf, &iattr))
         scale->abs_x = iattr;
      else
      {
         snprintf(attr_name_buf, sizeof(attr_name_buf), "scale_x%u", i);
         if (config_get_int(conf, attr_name_buf, &iattr))
            scale->abs_x = iattr;
      }
   }
   else
   {
      if (config_get_float(conf, attr_name_buf, &fattr))
         scale->scale_x = fattr;
      else
      {
         snprintf(attr_name_buf, sizeof(attr_name_buf), "scale_x%u", i);
         if (config_get_float(conf, attr_name_buf, &fattr))
            scale->scale_x = fattr;
      }
   }

   snprintf(attr_name_buf, sizeof(attr_name_buf), "scale%u", i);

   if (scale->type_y == RARCH_SCALE_ABSOLUTE)
   {
      if (config_get_int(conf, attr_name_buf, &iattr))
         scale->abs_y = iattr;
      else
      {
         snprintf(attr_name_buf, sizeof(attr_name_buf), "scale_y%u", i);
         if (config_get_int(conf, attr_name_buf, &iattr))
            scale->abs_y = iattr;
      }
   }
   else
   {
      if (config_get_float(conf, attr_name_buf, &fattr))
         scale->scale_y = fattr;
      else
      {
         snprintf(attr_name_buf, sizeof(attr_name_buf), "scale_y%u", i);
         if (config_get_float(conf, attr_name_buf, &fattr))
            scale->scale_y = fattr;
      }
   }

   return true;
}