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
typedef  int png_uint_32 ;
struct TYPE_4__ {unsigned int local_use; struct TYPE_4__* list; } ;
typedef  TYPE_1__ image_transform ;

/* Variables and functions */
 TYPE_1__ image_transform_end ; 
 TYPE_1__* image_transform_first ; 

__attribute__((used)) static int
image_transform_test_counter(png_uint_32 counter, unsigned int max)
{
   /* Test the list to see if there is any point contining, given a current
    * counter and a 'max' value.
    */
   image_transform *next = image_transform_first;

   while (next != &image_transform_end)
   {
      /* For max 0 or 1 continue until the counter overflows: */
      counter >>= 1;

      /* Continue if any entry hasn't reacked the max. */
      if (max > 1 && next->local_use < max)
         return 1;
      next = next->list;
   }

   return max <= 1 && counter == 0;
}