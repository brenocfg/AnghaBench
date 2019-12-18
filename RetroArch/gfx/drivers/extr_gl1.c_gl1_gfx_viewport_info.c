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
struct video_viewport {unsigned int full_width; unsigned int full_height; unsigned int y; unsigned int height; } ;
struct TYPE_2__ {struct video_viewport vp; } ;
typedef  TYPE_1__ gl1_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 

__attribute__((used)) static void gl1_gfx_viewport_info(void *data,
      struct video_viewport *vp)
{
   unsigned width, height;
   unsigned top_y, top_dist;
   gl1_t *gl1             = (gl1_t*)data;

   video_driver_get_size(&width, &height);

   *vp             = gl1->vp;
   vp->full_width  = width;
   vp->full_height = height;

   /* Adjust as GL viewport is bottom-up. */
   top_y           = vp->y + vp->height;
   top_dist        = height - top_y;
   vp->y           = top_dist;
}