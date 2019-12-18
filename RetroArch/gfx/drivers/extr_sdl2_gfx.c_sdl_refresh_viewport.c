#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct video_viewport {int x; int y; int width; int height; } ;
struct TYPE_11__ {scalar_t__ video_aspect_ratio_idx; } ;
struct TYPE_10__ {scalar_t__ video_scale_integer; } ;
struct TYPE_13__ {TYPE_2__ uints; TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_15__ {int x; int y; int width; int height; int full_width; int full_height; } ;
struct TYPE_12__ {scalar_t__ force_aspect; } ;
struct TYPE_14__ {int should_resize; TYPE_6__ vp; TYPE_3__ video; int /*<<< orphan*/  window; } ;
typedef  TYPE_5__ sdl2_video_t ;

/* Variables and functions */
 scalar_t__ ASPECT_RATIO_CUSTOM ; 
 int /*<<< orphan*/  SDL_GetWindowSize (int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_4__* config_get_ptr () ; 
 float fabsf (float) ; 
 scalar_t__ roundf (float) ; 
 int /*<<< orphan*/  sdl_refresh_renderer (TYPE_5__*) ; 
 float video_driver_get_aspect_ratio () ; 
 scalar_t__ video_viewport_get_custom () ; 
 int /*<<< orphan*/  video_viewport_get_scaled_integer (TYPE_6__*,int,int,float,scalar_t__) ; 

__attribute__((used)) static void sdl_refresh_viewport(sdl2_video_t *vid)
{
   int win_w, win_h;
   settings_t *settings = config_get_ptr();

   SDL_GetWindowSize(vid->window, &win_w, &win_h);

   vid->vp.x           = 0;
   vid->vp.y           = 0;
   vid->vp.width       = win_w;
   vid->vp.height      = win_h;
   vid->vp.full_width  = win_w;
   vid->vp.full_height = win_h;

   if (settings->bools.video_scale_integer)
      video_viewport_get_scaled_integer(&vid->vp,
            win_w, win_h, video_driver_get_aspect_ratio(),
            vid->video.force_aspect);
   else if (settings->uints.video_aspect_ratio_idx == ASPECT_RATIO_CUSTOM)
   {
      const struct video_viewport *custom =
         (const struct video_viewport*)video_viewport_get_custom();

      vid->vp.x = custom->x;
      vid->vp.y = custom->y;
      vid->vp.width  = custom->width;
      vid->vp.height = custom->height;
   }
   else if (vid->video.force_aspect)
   {
      float delta;
      float device_aspect  = (float)win_w / win_h;
      float desired_aspect = video_driver_get_aspect_ratio();

      if (fabsf(device_aspect - desired_aspect) < 0.0001f)
      {
         /* If the aspect ratios of screen and desired aspect ratio are
             * sufficiently equal (floating point stuff), assume they are
             * actually equal. */
      }
      else if (device_aspect > desired_aspect)
      {
         delta = (desired_aspect / device_aspect - 1.0f) / 2.0f + 0.5f;
         vid->vp.x     = (int)roundf(win_w * (0.5f - delta));
         vid->vp.width = (unsigned)roundf(2.0f * win_w * delta);
      }
      else
      {
         delta  = (device_aspect / desired_aspect - 1.0f) / 2.0f + 0.5f;
         vid->vp.y      = (int)roundf(win_h * (0.5f - delta));
         vid->vp.height = (unsigned)roundf(2.0f * win_h * delta);
      }
   }

   vid->should_resize = false;

   sdl_refresh_renderer(vid);
}