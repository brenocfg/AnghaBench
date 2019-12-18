#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  scaler; } ;
struct TYPE_4__ {int width; int bytes_per_pixel; int /*<<< orphan*/  height; TYPE_1__ menu; } ;
typedef  TYPE_2__ omap_video_t ;
typedef  enum scaler_pix_fmt { ____Placeholder_scaler_pix_fmt } scaler_pix_fmt ;

/* Variables and functions */
 int SCALER_FMT_ARGB8888 ; 
 int SCALER_FMT_RGBA4444 ; 
 int /*<<< orphan*/  video_frame_scale (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int,int,int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void omap_gfx_set_texture_frame(void *data, const void *frame, bool rgb32,
      unsigned width, unsigned height, float alpha)
{
   omap_video_t          *vid = (omap_video_t*)data;
   enum scaler_pix_fmt format = rgb32 ? SCALER_FMT_ARGB8888 : SCALER_FMT_RGBA4444;

   video_frame_scale(
         &vid->menu.scaler,
         vid->menu.frame,
         frame,
         format,
         vid->width,
         vid->height,
         vid->width * vid->bytes_per_pixel,
         width,
         height,
         width * (rgb32 ? sizeof(uint32_t) : sizeof(uint16_t)));
}