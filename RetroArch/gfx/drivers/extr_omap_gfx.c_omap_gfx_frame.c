#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {unsigned int out_height; unsigned int out_stride; } ;
struct TYPE_6__ {void const* frame; TYPE_1__ scaler; scalar_t__ active; } ;
struct TYPE_7__ {unsigned int width; unsigned int height; TYPE_2__ menu; int /*<<< orphan*/  omap; } ;
typedef  TYPE_3__ omap_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  menu_driver_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_render_msg (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  omapfb_blit_frame (int /*<<< orphan*/ ,void const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  omapfb_prepare (int /*<<< orphan*/ ) ; 
 scalar_t__ omapfb_set_mode (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static bool omap_gfx_frame(void *data, const void *frame, unsigned width,
      unsigned height, uint64_t frame_count, unsigned pitch, const char *msg,
      video_frame_info_t *video_info)
{
   omap_video_t *vid = (omap_video_t*)data;

   if (!frame)
      return true;

   if (width > 4 && height > 4 && (width != vid->width || height != vid->height))
   {
      RARCH_LOG("[video_omap]: mode set (resolution changed by core)\n");

      if (omapfb_set_mode(vid->omap, width, height) != 0)
      {
         RARCH_ERR("[video_omap]: mode set failed\n");
         return false;
      }

      vid->width = width;
      vid->height = height;
   }

   omapfb_prepare(vid->omap);
   omapfb_blit_frame(vid->omap, frame, vid->height, pitch);

#ifdef HAVE_MENU
   menu_driver_frame(video_info);
#endif

   if (vid->menu.active)
      omapfb_blit_frame(vid->omap, vid->menu.frame,
            vid->menu.scaler.out_height,
            vid->menu.scaler.out_stride);

   if (msg)
      omap_render_msg(vid, msg);

   return true;
}