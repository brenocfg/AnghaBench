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
 int list_defcmp (void*,void*,void*) ; 

void *
list_remove(list_t **list, void *data, int (*cmp)(void *, void *, void *),
    void *private)
{
	list_t *le, **le2;
	void *led;

	if (!cmp)
		cmp = list_defcmp;

	for (le = *list, le2 = list; le; le2 = &le->l_next, le = le->l_next) {
		if (cmp(le->l_data, data, private) == 0) {
			*le2 = le->l_next;
			led = le->l_data;
			free(le);
			return (led);
		}
	}

	return (NULL);
}