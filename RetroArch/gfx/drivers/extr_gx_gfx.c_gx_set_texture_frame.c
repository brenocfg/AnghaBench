#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * menu_data; } ;
typedef  TYPE_1__ gx_video_t ;

/* Variables and functions */

__attribute__((used)) static void gx_set_texture_frame(void *data, const void *frame,
      bool rgb32, unsigned width, unsigned height, float alpha)
{
   (void)rgb32;
   (void)width;
   (void)height;
   (void)alpha;

   gx_video_t *gx = (gx_video_t*)data;

   if (gx)
      gx->menu_data = (uint32_t*)frame;
}