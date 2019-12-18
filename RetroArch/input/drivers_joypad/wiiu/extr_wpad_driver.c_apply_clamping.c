#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_viewport {scalar_t__ x; scalar_t__ width; scalar_t__ y; scalar_t__ height; } ;
struct TYPE_3__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_1__ VPADTouchData ;

/* Variables and functions */

__attribute__((used)) static void apply_clamping(VPADTouchData *point, struct video_viewport *viewport, bool *clamped)
{
   /* clamp the x domain to the viewport */
   if (point->x < viewport->x)
   {
      point->x = viewport->x;
      *clamped = true;
   }
   else if (point->x > (viewport->x + viewport->width))
   {
      point->x = viewport->x + viewport->width;
      *clamped = true;
   }

   /* clamp the y domain to the viewport */
   if (point->y < viewport->y)
   {
      point->y = viewport->y;
      *clamped = true;
   }
   else if (point->y > (viewport->y + viewport->height))
   {
      point->y =  viewport->y + viewport->height;
      *clamped = true;
   }
}