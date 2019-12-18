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
struct TYPE_4__ {int size; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ MyList ;

/* Variables and functions */
 int /*<<< orphan*/  mylist_assign (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

void mylist_remove_at(MyList *list, int index)
{
   int i;

   if (index < 0 || index >= list->size)
      return;

   mylist_assign(list, index, NULL);

   for (i = index + 1; i < list->size; i++)
      list->data[i - 1] = list->data[i];

   list->size--;
   list->data[list->size] = NULL;
}