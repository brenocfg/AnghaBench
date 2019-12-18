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
struct TYPE_4__ {int size; void** data; } ;
typedef  TYPE_1__ MyList ;

/* Variables and functions */
 int /*<<< orphan*/  mylist_resize (TYPE_1__*,int,int) ; 

void mylist_push_back(MyList *list, void *value)
{
   int old_size;
   if (!list)
      return;
   old_size = list->size;
   mylist_resize(list, old_size + 1, false);
   list->data[old_size] = value;
}