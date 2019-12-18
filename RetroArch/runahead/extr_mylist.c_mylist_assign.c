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
struct TYPE_3__ {int size; void** data; int /*<<< orphan*/  (* destructor ) (void*) ;} ;
typedef  TYPE_1__ MyList ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*) ; 

void mylist_assign(MyList *list, int index, void *value)
{
   void *old_element = NULL;

   if (index < 0 || index >= list->size)
      return;

   old_element       = list->data[index];
   list->destructor(old_element);
   list->data[index] = value;
}