#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int custom_vp_x; int custom_vp_y; float custom_vp_width; float custom_vp_height; } ;
typedef  TYPE_3__ video_frame_info_t ;
struct TYPE_12__ {scalar_t__ video_aspect_ratio_idx; } ;
struct TYPE_11__ {scalar_t__ video_scale_integer; } ;
struct TYPE_14__ {TYPE_2__ uints; TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_16__ {float full_width; float full_height; int x; int y; float width; float height; } ;
struct TYPE_15__ {int rotation; int should_resize; TYPE_6__ vp; scalar_t__ keep_aspect; } ;
typedef  TYPE_5__ ctr_video_t ;

/* Variables and functions */
 scalar_t__ ASPECT_RATIO_CUSTOM ; 
 int /*<<< orphan*/  ctr_set_screen_coords (TYPE_5__*) ; 
 float fabsf (float) ; 
 scalar_t__ roundf (float) ; 
 float video_driver_get_aspect_ratio () ; 
 int /*<<< orphan*/  video_viewport_get_scaled_integer (TYPE_6__*,float,float,float,scalar_t__) ; 

__attribute__((used)) static void ctr_update_viewport(ctr_video_t* ctr, settings_t *settings, video_frame_info_t *video_info)
{
   int x                = 0;
   int y                = 0;
   float width          = ctr->vp.full_width;
   float height         = ctr->vp.full_height;
   float desired_aspect = video_driver_get_aspect_ratio();

   if(ctr->rotation & 0x1)
      desired_aspect = 1.0 / desired_aspect;

   if (settings->bools.video_scale_integer)
   {
      video_viewport_get_scaled_integer(&ctr->vp, ctr->vp.full_width,
            ctr->vp.full_height, desired_aspect, ctr->keep_aspect);
   }
   else if (ctr->keep_aspect)
   {
#if defined(HAVE_MENU)
      if (settings->uints.video_aspect_ratio_idx == ASPECT_RATIO_CUSTOM)
      {
         x      = video_info->custom_vp_x;
         y      = video_info->custom_vp_y;
         width  = video_info->custom_vp_width;
         height = video_info->custom_vp_height;
      }
      else
#endif
      {
         float delta;
         float device_aspect  = ((float)ctr->vp.full_width) / ctr->vp.full_height;

         if (fabsf(device_aspect - desired_aspect) < 0.0001f)
         {
            /* If the aspect ratios of screen and desired aspect
             * ratio are sufficiently equal (floating point stuff),
             * assume they are actually equal.
             */
         }
         else if (device_aspect > desired_aspect)
         {
            delta = (desired_aspect / device_aspect - 1.0f)
               / 2.0f + 0.5f;
            x     = (int)roundf(width * (0.5f - delta));
            width = (unsigned)roundf(2.0f * width * delta);
         }
         else
         {
            delta  = (device_aspect / desired_aspect - 1.0f)
               / 2.0f + 0.5f;
            y      = (int)roundf(height * (0.5f - delta));
            height = (unsigned)roundf(2.0f * height * delta);
         }
      }

      ctr->vp.x      = x;
      ctr->vp.y      = y;
      ctr->vp.width  = width;
      ctr->vp.height = height;
   }
   else
   {
      ctr->vp.x = ctr->vp.y = 0;
      ctr->vp.width = width;
      ctr->vp.height = height;
   }

   ctr_set_screen_coords(ctr);

   ctr->should_resize = false;

}