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
struct TYPE_4__ {void* l_data; struct TYPE_4__* l_next; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */

void
slist_merge(list_t **list1p, list_t *list2, int (*cmp)(void *, void *))
{
	list_t *list1, *next2;
	list_t *last1 = NULL;

	if (*list1p == NULL) {
		*list1p = list2;
		return;
	}

	list1 = *list1p;
	while (list2 != NULL) {
		if (cmp(list1->l_data, list2->l_data) > 0) {
			next2 = list2->l_next;

			if (last1 == NULL) {
				/* Insert at beginning */
				*list1p = last1 = list2;
				list2->l_next = list1;
			} else {
				list2->l_next = list1;
				last1->l_next = list2;
				last1 = list2;
			}

			list2 = next2;
		} else {

			last1 = list1;
			list1 = list1->l_next;

			if (list1 == NULL) {
				/* Add the rest to the end of list1 */
				last1->l_next = list2;
				list2 = NULL;
			}
		}
	}
}