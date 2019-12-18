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
struct TYPE_2__ {unsigned int video_width; unsigned int video_height; struct video_viewport vp; } ;
typedef  TYPE_1__ gl_t ;

/* Variables and functions */

__attribute__((used)) static void gl2_viewport_info(void *data, struct video_viewport *vp)
{
   unsigned top_y, top_dist;
   gl_t *gl        = (gl_t*)data;
   unsigned width  = gl->video_width;
   unsigned height = gl->video_height;

   *vp             = gl->vp;
   vp->full_width  = width;
   vp->full_height = height;

   /* Adjust as GL viewport is bottom-up. */
   top_y           = vp->y + vp->height;
   top_dist        = height - top_y;
   vp->y           = top_dist;
}