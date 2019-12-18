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
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
list_free(list_t *list, void (*datafree)(void *, void *), void *private)
{
	list_t *le;

	while (list) {
		le = list;
		list = list->l_next;
		if (le->l_data && datafree)
			datafree(le->l_data, private);
		free(le);
	}
}