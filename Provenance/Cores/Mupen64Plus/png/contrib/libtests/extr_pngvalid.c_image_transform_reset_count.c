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
struct TYPE_4__ {struct TYPE_4__* list; scalar_t__ next; scalar_t__ local_use; } ;
typedef  TYPE_1__ image_transform ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 TYPE_1__ image_transform_end ; 
 TYPE_1__* image_transform_first ; 

__attribute__((used)) static void
image_transform_reset_count(void)
{
   image_transform *next = image_transform_first;
   int count = 0;

   while (next != &image_transform_end)
   {
      next->local_use = 0;
      next->next = 0;
      next = next->list;
      ++count;
   }

   /* This can only happen if we every have more than 32 transforms (excluding
    * the end) in the list.
    */
   if (count > 32) abort();
}