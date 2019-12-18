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
typedef  int video_layout_orientation_t ;
struct TYPE_5__ {float x; float y; float w; float h; } ;
typedef  TYPE_1__ video_layout_bounds_t ;
struct TYPE_6__ {unsigned int components_count; TYPE_3__* components; } ;
typedef  TYPE_2__ element_t ;
struct TYPE_7__ {int orientation; TYPE_1__ bounds; } ;
typedef  TYPE_3__ component_t ;

/* Variables and functions */
 int VIDEO_LAYOUT_FLIP_X ; 
 int VIDEO_LAYOUT_FLIP_Y ; 
 int VIDEO_LAYOUT_SWAP_XY ; 

void element_apply_orientation(element_t *elem, video_layout_orientation_t orientation)
{
   unsigned i;

   for (i = 0; i < elem->components_count; ++i)
   {
      component_t *comp = &elem->components[i];
      comp->orientation ^= orientation;

      if (orientation & VIDEO_LAYOUT_SWAP_XY)
      {
         video_layout_bounds_t b;
         b = comp->bounds;

         comp->bounds.x = b.y;
         comp->bounds.y = b.x;
         comp->bounds.w = b.h;
         comp->bounds.h = b.w;
      }

      if (orientation & VIDEO_LAYOUT_FLIP_X)
         comp->bounds.x = 1.0f - comp->bounds.x - comp->bounds.w;

      if (orientation & VIDEO_LAYOUT_FLIP_Y)
         comp->bounds.y = 1.0f - comp->bounds.y - comp->bounds.h;
   }
}