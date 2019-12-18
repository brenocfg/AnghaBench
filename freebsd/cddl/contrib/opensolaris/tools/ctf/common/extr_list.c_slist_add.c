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
 int /*<<< orphan*/  list_add (TYPE_1__**,void*) ; 

void
slist_add(list_t **list, void *data, int (*cmp)(void *, void *))
{
	list_t **nextp;

	for (nextp = list; *nextp; nextp = &((*nextp)->l_next)) {
		if (cmp((*nextp)->l_data, data) > 0)
			break;
	}

	list_add(nextp, data);
}