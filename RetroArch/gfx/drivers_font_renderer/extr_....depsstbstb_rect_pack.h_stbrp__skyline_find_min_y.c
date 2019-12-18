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
struct TYPE_3__ {int x; int y; struct TYPE_3__* next; } ;
typedef  TYPE_1__ stbrp_node ;
typedef  int /*<<< orphan*/  stbrp_context ;

/* Variables and functions */
 int /*<<< orphan*/  STBRP_ASSERT (int) ; 

__attribute__((used)) static int stbrp__skyline_find_min_y(stbrp_context *c,
      stbrp_node *first, int x0, int width, int *pwaste)
{
   int min_y, visited_width, waste_area;
   stbrp_node *node = first;
   int x1 = x0 + width;

   STBRP_ASSERT(first->x <= x0);
   STBRP_ASSERT(node->next->x > x0);
   STBRP_ASSERT(node->x <= x0);

   min_y = 0;
   waste_area = 0;
   visited_width = 0;
   while (node->x < x1)
   {
      if (node->y > min_y)
      {
         /* raise min_y higher.
          * we've accounted for all waste up to min_y,
          * but we'll now add more waste for everything we've visted
          */
         waste_area += visited_width * (node->y - min_y);
         min_y = node->y;

         /* the first time through, visited_width might be reduced */
         if (node->x < x0)
            visited_width += node->next->x - x0;
         else
            visited_width += node->next->x - node->x;
      }
      else
      {
         /* add waste area */
         int under_width = node->next->x - node->x;
         if (under_width + visited_width > width)
            under_width = width - visited_width;
         waste_area += under_width * (min_y - node->y);
         visited_width += under_width;
      }
      node = node->next;
   }

   *pwaste = waste_area;
   return min_y;
}