#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  caca_create_display (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caca_create_dither (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  caca_cv ; 
 int /*<<< orphan*/  caca_display ; 
 int /*<<< orphan*/  caca_dither ; 
 int /*<<< orphan*/  caca_get_canvas (int /*<<< orphan*/ ) ; 
 scalar_t__ caca_get_canvas_height (int /*<<< orphan*/ ) ; 
 scalar_t__ caca_get_canvas_width (int /*<<< orphan*/ ) ; 
 scalar_t__ caca_rgb32 ; 
 scalar_t__ caca_video_height ; 
 int /*<<< orphan*/  caca_video_pitch ; 
 scalar_t__ caca_video_width ; 
 int /*<<< orphan*/  video_driver_set_size (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void caca_gfx_create(void)
{
   caca_display = caca_create_display(NULL);
   caca_cv = caca_get_canvas(caca_display);

   if(!caca_video_width || !caca_video_height)
   {
      caca_video_width = caca_get_canvas_width(caca_cv);
      caca_video_height = caca_get_canvas_height(caca_cv);
   }

   if (caca_rgb32)
      caca_dither = caca_create_dither(32, caca_video_width, caca_video_height, caca_video_pitch,
                            0x00ff0000, 0xff00, 0xff, 0x0);
   else
      caca_dither = caca_create_dither(16, caca_video_width, caca_video_height, caca_video_pitch,
                            0xf800, 0x7e0, 0x1f, 0x0);

   video_driver_set_size(&caca_video_width, &caca_video_height);
}