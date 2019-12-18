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
struct TYPE_3__ {unsigned int rotation; int should_resize; } ;
typedef  TYPE_1__ wiiu_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  wiiu_set_projection (TYPE_1__*) ; 

__attribute__((used)) static void wiiu_gfx_set_rotation(void *data,
                                  unsigned rotation)
{
   wiiu_video_t *wiiu = (wiiu_video_t *) data;

   if (wiiu)
   {
      wiiu->rotation = rotation;
      wiiu_set_projection(wiiu);
      wiiu->should_resize = true;
   }
}