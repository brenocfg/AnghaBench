#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  max_swapchain_images; } ;
typedef  TYPE_1__ video_frame_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct dispmanx_video {unsigned int core_width; unsigned int core_height; float aspect_ratio; unsigned int core_pitch; int /*<<< orphan*/ * main_surface; int /*<<< orphan*/ * menu_surface; scalar_t__ menu_active; scalar_t__ rgb32; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_IMAGE_RGB565 ; 
 int /*<<< orphan*/  VC_IMAGE_XRGB8888 ; 
 int /*<<< orphan*/  dispmanx_surface_free (struct dispmanx_video*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dispmanx_surface_setup (struct dispmanx_video*,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dispmanx_surface_update (struct dispmanx_video*,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_driver_frame (TYPE_1__*) ; 
 float video_driver_get_aspect_ratio () ; 

__attribute__((used)) static bool dispmanx_gfx_frame(void *data, const void *frame, unsigned width,
      unsigned height, uint64_t frame_count, unsigned pitch, const char *msg,
      video_frame_info_t *video_info)
{
   struct dispmanx_video *_dispvars = data;
   float aspect = video_driver_get_aspect_ratio();

   if (!frame)
      return true;

   if (  (width != _dispvars->core_width)   ||
         (height != _dispvars->core_height) ||
         (_dispvars->aspect_ratio != aspect))
   {
      /* Sanity check. */
      if (width == 0 || height == 0)
         return true;

      _dispvars->core_width    = width;
      _dispvars->core_height   = height;
      _dispvars->core_pitch    = pitch;
      _dispvars->aspect_ratio  = aspect;

      if (_dispvars->main_surface != NULL)
         dispmanx_surface_free(_dispvars, &_dispvars->main_surface);

      /* Internal resolution or ratio has changed, so we need
       * to recreate the main surface. */
      dispmanx_surface_setup(_dispvars,
            width,
            height,
            pitch,
            _dispvars->rgb32 ? 32 : 16,
            _dispvars->rgb32 ? VC_IMAGE_XRGB8888 : VC_IMAGE_RGB565,
            255,
            _dispvars->aspect_ratio,
            video_info->max_swapchain_images,
            0,
            &_dispvars->main_surface);

      /* We need to recreate the menu surface too, if it exists already, so we
       * free it and let dispmanx_set_texture_frame() recreate it as it detects it's NULL.*/
      if (_dispvars->menu_active && _dispvars->menu_surface)
         dispmanx_surface_free(_dispvars, &_dispvars->menu_surface);
   }

#ifdef HAVE_MENU
   menu_driver_frame(video_info);
#endif

   /* Update main surface: locate free page, blit and flip. */
   dispmanx_surface_update(_dispvars, frame, _dispvars->main_surface);
   return true;
}