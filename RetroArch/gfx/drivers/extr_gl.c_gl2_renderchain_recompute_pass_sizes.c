#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct video_fbo_rect {unsigned int img_width; unsigned int max_img_width; unsigned int img_height; unsigned int max_img_height; } ;
struct gfx_fbo_scale {int type_x; unsigned int scale_x; unsigned int abs_x; int type_y; unsigned int scale_y; unsigned int abs_y; } ;
struct TYPE_5__ {unsigned int tex_w; unsigned int tex_h; int rotation; struct video_fbo_rect* fbo_rect; } ;
typedef  TYPE_1__ gl_t ;
struct TYPE_6__ {struct gfx_fbo_scale* fbo_scale; scalar_t__ fbo_pass; } ;
typedef  TYPE_2__ gl2_renderchain_data_t ;
typedef  void* GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_MAX_TEXTURE_SIZE ; 
#define  RARCH_SCALE_ABSOLUTE 130 
#define  RARCH_SCALE_INPUT 129 
#define  RARCH_SCALE_VIEWPORT 128 
 int /*<<< orphan*/  RARCH_WARN (char*,void*,void*) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static void gl2_renderchain_recompute_pass_sizes(
      gl_t *gl,
      gl2_renderchain_data_t *chain,
      unsigned width, unsigned height,
      unsigned vp_width, unsigned vp_height)
{
   unsigned i;
   bool size_modified       = false;
   GLint max_size           = 0;
   unsigned last_width      = width;
   unsigned last_height     = height;
   unsigned last_max_width  = gl->tex_w;
   unsigned last_max_height = gl->tex_h;

   glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_size);

   /* Calculate viewports for FBOs. */
   for (i = 0; i < (unsigned)chain->fbo_pass; i++)
   {
      struct video_fbo_rect  *fbo_rect   = &gl->fbo_rect[i];
      struct gfx_fbo_scale *fbo_scale    = &chain->fbo_scale[i];

      switch (fbo_scale->type_x)
      {
         case RARCH_SCALE_INPUT:
            fbo_rect->img_width      = fbo_scale->scale_x * last_width;
            fbo_rect->max_img_width  = last_max_width     * fbo_scale->scale_x;
            break;

         case RARCH_SCALE_ABSOLUTE:
            fbo_rect->img_width      = fbo_rect->max_img_width =
               fbo_scale->abs_x;
            break;

         case RARCH_SCALE_VIEWPORT:
            if (gl->rotation % 180 == 90)
            {
               fbo_rect->img_width      = fbo_rect->max_img_width =
               fbo_scale->scale_x * vp_height;
            } else {
               fbo_rect->img_width      = fbo_rect->max_img_width =
               fbo_scale->scale_x * vp_width;
            }
            break;
      }

      switch (fbo_scale->type_y)
      {
         case RARCH_SCALE_INPUT:
            fbo_rect->img_height     = last_height * fbo_scale->scale_y;
            fbo_rect->max_img_height = last_max_height * fbo_scale->scale_y;
            break;

         case RARCH_SCALE_ABSOLUTE:
            fbo_rect->img_height     = fbo_scale->abs_y;
            fbo_rect->max_img_height = fbo_scale->abs_y;
            break;

         case RARCH_SCALE_VIEWPORT:
            if (gl->rotation % 180 == 90)
            {
               fbo_rect->img_height      = fbo_rect->max_img_height =
               fbo_scale->scale_y * vp_width;
            } else {
            fbo_rect->img_height     = fbo_rect->max_img_height =
               fbo_scale->scale_y * vp_height;
            }
            break;
      }

      if (fbo_rect->img_width > (unsigned)max_size)
      {
         size_modified            = true;
         fbo_rect->img_width      = max_size;
      }

      if (fbo_rect->img_height > (unsigned)max_size)
      {
         size_modified            = true;
         fbo_rect->img_height     = max_size;
      }

      if (fbo_rect->max_img_width > (unsigned)max_size)
      {
         size_modified            = true;
         fbo_rect->max_img_width  = max_size;
      }

      if (fbo_rect->max_img_height > (unsigned)max_size)
      {
         size_modified            = true;
         fbo_rect->max_img_height = max_size;
      }

      if (size_modified)
         RARCH_WARN("FBO textures exceeded maximum size of GPU (%dx%d). Resizing to fit.\n", max_size, max_size);

      last_width      = fbo_rect->img_width;
      last_height     = fbo_rect->img_height;
      last_max_width  = fbo_rect->max_img_width;
      last_max_height = fbo_rect->max_img_height;
   }
}