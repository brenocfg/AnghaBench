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
struct TYPE_3__ {void* l_data; struct TYPE_3__* l_next; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */

int
list_iter(list_t *list, int (*func)(void *, void *), void *private)
{
	list_t *lnext;
	int cumrc = 0;
	int cbrc;

	while (list) {
		lnext = list->l_next;
		if ((cbrc = func(list->l_data, private)) < 0)
			return (cbrc);
		cumrc += cbrc;
		list = lnext;
	}

	return (cumrc);
}