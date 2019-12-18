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
struct video_viewport {unsigned int full_width; unsigned int full_height; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_3__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_4__ {TYPE_1__ final_viewport; } ;
typedef  TYPE_2__ d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 

__attribute__((used)) static void d3d9_viewport_info(void *data, struct video_viewport *vp)
{
   unsigned width, height;
   d3d9_video_t *d3d   = (d3d9_video_t*)data;

   if (!vp)
      return;

   video_driver_get_size(&width, &height);

   vp->x            = d3d->final_viewport.X;
   vp->y            = d3d->final_viewport.Y;
   vp->width        = d3d->final_viewport.Width;
   vp->height       = d3d->final_viewport.Height;

   vp->full_width   = width;
   vp->full_height  = height;
}