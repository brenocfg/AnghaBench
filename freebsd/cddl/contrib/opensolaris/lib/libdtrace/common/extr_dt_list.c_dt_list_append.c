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
struct TYPE_3__ {struct TYPE_3__* dl_next; struct TYPE_3__* dl_prev; } ;
typedef  TYPE_1__ dt_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
dt_list_append(dt_list_t *dlp, void *new)
{
	dt_list_t *p = dlp->dl_prev;	/* p = tail list element */
	dt_list_t *q = new;		/* q = new list element */

	dlp->dl_prev = q;
	q->dl_prev = p;
	q->dl_next = NULL;

	if (p != NULL) {
		assert(p->dl_next == NULL);
		p->dl_next = q;
	} else {
		assert(dlp->dl_next == NULL);
		dlp->dl_next = q;
	}
}