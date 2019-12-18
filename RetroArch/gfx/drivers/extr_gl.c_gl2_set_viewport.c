#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int height; scalar_t__ aspect_ratio_idx; int custom_vp_x; unsigned int custom_vp_y; unsigned int custom_vp_height; unsigned int custom_vp_width; scalar_t__ scale_integer; } ;
typedef  TYPE_1__ video_frame_info_t ;
struct TYPE_12__ {unsigned int width; unsigned int height; int x; int y; } ;
struct TYPE_10__ {unsigned int vp_out_width; unsigned int vp_out_height; TYPE_4__ vp; scalar_t__ keep_aspect; } ;
typedef  TYPE_2__ gl_t ;
struct TYPE_11__ {float* aspect; unsigned int width; unsigned int height; } ;
typedef  TYPE_3__ gfx_ctx_aspect_t ;

/* Variables and functions */
 scalar_t__ ASPECT_RATIO_CUSTOM ; 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  default_ortho ; 
 float fabsf (float) ; 
 int /*<<< orphan*/  gl2_set_projection (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  glViewport (int,int,unsigned int,unsigned int) ; 
 scalar_t__ roundf (float) ; 
 int /*<<< orphan*/  video_context_driver_translate_aspect (TYPE_3__*) ; 
 float video_driver_get_aspect_ratio () ; 
 int /*<<< orphan*/  video_viewport_get_scaled_integer (TYPE_4__*,unsigned int,unsigned int,float,scalar_t__) ; 

__attribute__((used)) static void gl2_set_viewport(gl_t *gl,
      video_frame_info_t *video_info,
      unsigned viewport_width,
      unsigned viewport_height,
      bool force_full, bool allow_rotate)
{
   gfx_ctx_aspect_t aspect_data;
   int x                    = 0;
   int y                    = 0;
   float device_aspect      = (float)viewport_width / viewport_height;
   unsigned height          = video_info->height;

   aspect_data.aspect       = &device_aspect;
   aspect_data.width        = viewport_width;
   aspect_data.height       = viewport_height;

   video_context_driver_translate_aspect(&aspect_data);

   if (video_info->scale_integer && !force_full)
   {
      video_viewport_get_scaled_integer(&gl->vp,
            viewport_width, viewport_height,
            video_driver_get_aspect_ratio(), gl->keep_aspect);
      viewport_width  = gl->vp.width;
      viewport_height = gl->vp.height;
   }
   else if (gl->keep_aspect && !force_full)
   {
      float desired_aspect = video_driver_get_aspect_ratio();

#if defined(HAVE_MENU)
      if (video_info->aspect_ratio_idx == ASPECT_RATIO_CUSTOM)
      {
         /* GL has bottom-left origin viewport. */
         x      = video_info->custom_vp_x;
         y      = height - video_info->custom_vp_y - video_info->custom_vp_height;
         viewport_width  = video_info->custom_vp_width;
         viewport_height = video_info->custom_vp_height;
      }
      else
#endif
      {
         float delta;

         if (fabsf(device_aspect - desired_aspect) < 0.0001f)
         {
            /* If the aspect ratios of screen and desired aspect
             * ratio are sufficiently equal (floating point stuff),
             * assume they are actually equal.
             */
         }
         else if (device_aspect > desired_aspect)
         {
            delta = (desired_aspect / device_aspect - 1.0f) / 2.0f + 0.5f;
            x     = (int)roundf(viewport_width * (0.5f - delta));
            viewport_width = (unsigned)roundf(2.0f * viewport_width * delta);
         }
         else
         {
            delta  = (device_aspect / desired_aspect - 1.0f) / 2.0f + 0.5f;
            y      = (int)roundf(viewport_height * (0.5f - delta));
            viewport_height = (unsigned)roundf(2.0f * viewport_height * delta);
         }
      }

      gl->vp.x      = x;
      gl->vp.y      = y;
      gl->vp.width  = viewport_width;
      gl->vp.height = viewport_height;
   }
   else
   {
      gl->vp.x      = gl->vp.y = 0;
      gl->vp.width  = viewport_width;
      gl->vp.height = viewport_height;
   }

#if defined(RARCH_MOBILE)
   /* In portrait mode, we want viewport to gravitate to top of screen. */
   if (device_aspect < 1.0f)
      gl->vp.y *= 2;
#endif

   glViewport(gl->vp.x, gl->vp.y, gl->vp.width, gl->vp.height);
   gl2_set_projection(gl, &default_ortho, allow_rotate);

   /* Set last backbuffer viewport. */
   if (!force_full)
   {
      gl->vp_out_width  = viewport_width;
      gl->vp_out_height = viewport_height;
   }

#if 0
   RARCH_LOG("Setting viewport @ %ux%u\n", viewport_width, viewport_height);
#endif
}