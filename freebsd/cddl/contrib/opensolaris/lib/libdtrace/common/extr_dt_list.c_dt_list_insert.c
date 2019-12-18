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
struct TYPE_4__ {struct TYPE_4__* dl_prev; struct TYPE_4__* dl_next; } ;
typedef  TYPE_1__ dt_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_list_append (TYPE_1__*,void*) ; 

void
dt_list_insert(dt_list_t *dlp, void *after_me, void *new)
{
	dt_list_t *p = after_me;
	dt_list_t *q = new;

	if (p == NULL || p->dl_next == NULL) {
		dt_list_append(dlp, new);
		return;
	}

	q->dl_next = p->dl_next;
	q->dl_prev = p;
	p->dl_next = q;
	q->dl_next->dl_prev = q;
}