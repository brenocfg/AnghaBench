#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float margins_screen_top; float icon_size; } ;
typedef  TYPE_1__ stripes_handle_t ;

/* Variables and functions */
 float stripes_item_y (TYPE_1__ const*,unsigned int,unsigned int) ; 

__attribute__((used)) static void stripes_calculate_visible_range(const stripes_handle_t *stripes,
      unsigned height, size_t list_size, unsigned current,
      unsigned *first, unsigned *last)
{
   unsigned j;
   float    base_y = stripes->margins_screen_top;

   *first = 0;
   *last  = list_size ? list_size - 1 : 0;

   if (current)
   {
      for (j = current; j-- > 0; )
      {
         float bottom = stripes_item_y(stripes, j, current)
            + base_y + stripes->icon_size;

         if (bottom < 0)
            break;

         *first = j;
      }
   }

   for (j = current+1; j < list_size; j++)
   {
      float top = stripes_item_y(stripes, j, current) + base_y;

      if (top > height)
         break;

      *last = j;
   }
}