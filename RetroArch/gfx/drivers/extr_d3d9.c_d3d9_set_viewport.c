#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int X; int Y; unsigned int Width; unsigned int Height; float MinZ; float MaxZ; } ;
struct TYPE_5__ {TYPE_1__ final_viewport; } ;
typedef  TYPE_2__ d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_calculate_rect (void*,unsigned int*,unsigned int*,int*,int*,int,int) ; 
 int /*<<< orphan*/  d3d9_set_font_rect (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void d3d9_set_viewport(void *data,
      unsigned width, unsigned height,
      bool force_full,
      bool allow_rotate)
{
   int x               = 0;
   int y               = 0;
   d3d9_video_t *d3d   = (d3d9_video_t*)data;

   d3d9_calculate_rect(data, &width, &height, &x, &y,
         force_full, allow_rotate);

   /* D3D doesn't support negative X/Y viewports ... */
   if (x < 0)
      x = 0;
   if (y < 0)
      y = 0;

   d3d->final_viewport.X      = x;
   d3d->final_viewport.Y      = y;
   d3d->final_viewport.Width  = width;
   d3d->final_viewport.Height = height;
   d3d->final_viewport.MinZ   = 0.0f;
   d3d->final_viewport.MaxZ   = 1.0f;

   d3d9_set_font_rect(d3d, NULL);
}