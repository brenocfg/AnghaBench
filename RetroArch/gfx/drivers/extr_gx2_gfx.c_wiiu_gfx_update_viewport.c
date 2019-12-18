#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {unsigned int width; unsigned int height; int x; int y; } ;
struct TYPE_11__ {unsigned int width; unsigned int height; } ;
struct TYPE_12__ {TYPE_1__ surface; } ;
struct TYPE_15__ {TYPE_9__ vp; scalar_t__ keep_aspect; TYPE_2__ color_buffer; } ;
typedef  TYPE_5__ wiiu_video_t ;
struct video_viewport {int x; int y; unsigned int width; unsigned int height; } ;
struct TYPE_14__ {scalar_t__ video_aspect_ratio_idx; } ;
struct TYPE_13__ {scalar_t__ video_scale_integer; } ;
struct TYPE_16__ {TYPE_4__ uints; TYPE_3__ bools; } ;
typedef  TYPE_6__ settings_t ;

/* Variables and functions */
 scalar_t__ ASPECT_RATIO_CUSTOM ; 
 TYPE_6__* config_get_ptr () ; 
 float fabsf (float) ; 
 scalar_t__ roundf (float) ; 
 float video_driver_get_aspect_ratio () ; 
 struct video_viewport* video_viewport_get_custom () ; 
 int /*<<< orphan*/  video_viewport_get_scaled_integer (TYPE_9__*,unsigned int,unsigned int,float,scalar_t__) ; 
 int /*<<< orphan*/  wiiu_set_projection (TYPE_5__*) ; 

__attribute__((used)) static void wiiu_gfx_update_viewport(wiiu_video_t *wiiu)
{
   int x                    = 0;
   int y                    = 0;
   unsigned viewport_width  = wiiu->color_buffer.surface.width;
   unsigned viewport_height = wiiu->color_buffer.surface.height;
   float device_aspect      = (float)viewport_width / viewport_height;
   settings_t *settings     = config_get_ptr();

   if (settings->bools.video_scale_integer)
   {
      video_viewport_get_scaled_integer(&wiiu->vp,
            viewport_width, viewport_height,
            video_driver_get_aspect_ratio(), wiiu->keep_aspect);
      viewport_width  = wiiu->vp.width;
      viewport_height = wiiu->vp.height;
   }
   else if (wiiu->keep_aspect)
   {
      float desired_aspect = video_driver_get_aspect_ratio();

#if defined(HAVE_MENU)

      if (settings->uints.video_aspect_ratio_idx == ASPECT_RATIO_CUSTOM)
      {
         const struct video_viewport *custom = video_viewport_get_custom();

         /* Vulkan has top-left origin viewport. */
         x               = custom->x;
         y               = custom->y;
         viewport_width  = custom->width;
         viewport_height = custom->height;
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
            delta          = (desired_aspect / device_aspect - 1.0f)
                             / 2.0f + 0.5f;
            x              = (int)roundf(viewport_width * (0.5f - delta));
            viewport_width = (unsigned)roundf(2.0f * viewport_width * delta);
         }
         else
         {
            delta           = (device_aspect / desired_aspect - 1.0f)
                              / 2.0f + 0.5f;
            y               = (int)roundf(viewport_height * (0.5f - delta));
            viewport_height = (unsigned)roundf(2.0f * viewport_height * delta);
         }
      }

      wiiu->vp.x      = x;
      wiiu->vp.y      = y;
      wiiu->vp.width  = viewport_width;
      wiiu->vp.height = viewport_height;
   }
   else
   {
      wiiu->vp.x      = 0;
      wiiu->vp.y      = 0;
      wiiu->vp.width  = viewport_width;
      wiiu->vp.height = viewport_height;
   }

   wiiu_set_projection(wiiu);
}