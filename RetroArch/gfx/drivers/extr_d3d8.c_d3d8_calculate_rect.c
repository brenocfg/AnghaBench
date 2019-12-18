#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int x; int y; unsigned int width; unsigned int height; } ;
typedef  TYPE_3__ video_viewport_t ;
struct video_viewport {int x; int y; unsigned int width; unsigned int height; scalar_t__ full_height; scalar_t__ full_width; } ;
struct TYPE_9__ {scalar_t__ video_aspect_ratio_idx; } ;
struct TYPE_8__ {scalar_t__ video_scale_integer; } ;
struct TYPE_11__ {TYPE_2__ uints; TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_12__ {scalar_t__ keep_aspect; } ;
typedef  TYPE_5__ d3d8_video_t ;

/* Variables and functions */
 scalar_t__ ASPECT_RATIO_CUSTOM ; 
 TYPE_4__* config_get_ptr () ; 
 float fabsf (float) ; 
 scalar_t__ roundf (float) ; 
 float video_driver_get_aspect_ratio () ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 
 TYPE_3__* video_viewport_get_custom () ; 
 int /*<<< orphan*/  video_viewport_get_scaled_integer (struct video_viewport*,unsigned int,unsigned int,float,scalar_t__) ; 

__attribute__((used)) static void d3d8_calculate_rect(void *data,
      unsigned *width, unsigned *height,
      int *x, int *y,
      bool force_full,
      bool allow_rotate)
{
   float device_aspect  = (float)*width / *height;
   d3d8_video_t *d3d     = (d3d8_video_t*)data;
   settings_t *settings = config_get_ptr();

   video_driver_get_size(width, height);

   *x                   = 0;
   *y                   = 0;

   if (settings->bools.video_scale_integer && !force_full)
   {
      struct video_viewport vp;

      vp.x                        = 0;
      vp.y                        = 0;
      vp.width                    = 0;
      vp.height                   = 0;
      vp.full_width               = 0;
      vp.full_height              = 0;

      video_viewport_get_scaled_integer(&vp,
            *width,
            *height,
            video_driver_get_aspect_ratio(),
            d3d->keep_aspect);

      *x                          = vp.x;
      *y                          = vp.y;
      *width                      = vp.width;
      *height                     = vp.height;
   }
   else if (d3d->keep_aspect && !force_full)
   {
      float desired_aspect = video_driver_get_aspect_ratio();

#if defined(HAVE_MENU)
      if (settings->uints.video_aspect_ratio_idx == ASPECT_RATIO_CUSTOM)
      {
         video_viewport_t *custom = video_viewport_get_custom();

         *x          = custom->x;
         *y          = custom->y;
         *width      = custom->width;
         *height     = custom->height;
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
            delta        = (desired_aspect / device_aspect - 1.0f) / 2.0f + 0.5f;
            *x           = (int)(roundf(*width * (0.5f - delta)));
            *width       = (unsigned)(roundf(2.0f * (*width) * delta));
         }
         else
         {
            delta        = (device_aspect / desired_aspect - 1.0f) / 2.0f + 0.5f;
            *y           = (int)(roundf(*height * (0.5f - delta)));
            *height      = (unsigned)(roundf(2.0f * (*height) * delta));
         }
      }
   }
}