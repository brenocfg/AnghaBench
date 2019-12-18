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
struct TYPE_4__ {struct TYPE_4__* l_next; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */

void
list_concat(list_t **list1, list_t *list2)
{
	list_t *l, *last;

	for (l = *list1, last = NULL; l; last = l, l = l->l_next)
		continue;

	if (last == NULL)
		*list1 = list2;
	else
		last->l_next = list2;
}