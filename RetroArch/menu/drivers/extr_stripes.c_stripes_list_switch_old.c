#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float alpha; float label_alpha; float x; } ;
typedef  TYPE_1__ stripes_node_t ;
struct TYPE_7__ {int icon_spacing_horizontal; } ;
typedef  TYPE_2__ stripes_handle_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 size_t file_list_get_size (int /*<<< orphan*/ *) ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  stripes_calculate_visible_range (TYPE_2__*,unsigned int,size_t,size_t,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  stripes_push_animations (TYPE_1__*,uintptr_t,float,float) ; 
 int /*<<< orphan*/  video_driver_get_size (int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static void stripes_list_switch_old(stripes_handle_t *stripes,
      file_list_t *list, int dir, size_t current)
{
   unsigned i, first, last, height;
   size_t end = file_list_get_size(list);
   float ix   = -stripes->icon_spacing_horizontal * dir;
   float ia   = 0;

   first = 0;
   last  = end > 0 ? end - 1 : 0;

   video_driver_get_size(NULL, &height);
   stripes_calculate_visible_range(stripes, height, end,
         current, &first, &last);

   for (i = 0; i < end; i++)
   {
      stripes_node_t *node = (stripes_node_t*)
         file_list_get_userdata_at_offset(list, i);

      if (!node)
         continue;

      if (i >= first && i <= last)
         stripes_push_animations(node, (uintptr_t)list, ia, ix);
      else
      {
         node->alpha = node->label_alpha = ia;
         node->x     = ix;
      }
   }
}