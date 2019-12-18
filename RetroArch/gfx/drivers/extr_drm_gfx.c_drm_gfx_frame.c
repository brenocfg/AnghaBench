#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  context_data; int /*<<< orphan*/  (* cb_update_window_title ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ video_frame_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_video {unsigned int core_width; unsigned int core_height; unsigned int core_pitch; int /*<<< orphan*/ * main_surface; int /*<<< orphan*/  current_aspect; scalar_t__ rgb32; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_FORMAT_RGB565 ; 
 int /*<<< orphan*/  DRM_FORMAT_XRGB8888 ; 
 int /*<<< orphan*/  drm_plane_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_surface_free (struct drm_video*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  drm_surface_setup (struct drm_video*,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  drm_surface_update (struct drm_video*,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_driver_frame (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static bool drm_gfx_frame(void *data, const void *frame, unsigned width,
      unsigned height, uint64_t frame_count, unsigned pitch, const char *msg,
      video_frame_info_t *video_info)
{
   struct drm_video *_drmvars = data;

   if (  ( width != _drmvars->core_width) ||
         (height != _drmvars->core_height))
   {
      /* Sanity check. */
      if (width == 0 || height == 0)
         return true;

      _drmvars->core_width  = width;
      _drmvars->core_height = height;
      _drmvars->core_pitch  = pitch;

      if (_drmvars->main_surface != NULL)
         drm_surface_free(_drmvars, &_drmvars->main_surface);

      /* We need to recreate the main surface and it's pages (buffers). */
      drm_surface_setup(_drmvars,
            width,
            height,
            pitch,
            _drmvars->rgb32 ? 4 : 2,
            _drmvars->rgb32 ? DRM_FORMAT_XRGB8888 : DRM_FORMAT_RGB565,
	    255,
            _drmvars->current_aspect,
            3,
            0,
            &_drmvars->main_surface);

      /* We need to change the plane to read from the main surface */
      drm_plane_setup(_drmvars->main_surface);
   }

#ifdef HAVE_MENU
   menu_driver_frame(video_info);
#endif

   video_info->cb_update_window_title(
         video_info->context_data, video_info);

   /* Update main surface: locate free page, blit and flip. */
   drm_surface_update(_drmvars, frame, _drmvars->main_surface);
   return true;
}