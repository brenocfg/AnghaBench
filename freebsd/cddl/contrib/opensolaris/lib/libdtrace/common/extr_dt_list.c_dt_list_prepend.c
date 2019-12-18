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
struct TYPE_3__ {struct TYPE_3__* dl_prev; struct TYPE_3__* dl_next; } ;
typedef  TYPE_1__ dt_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
dt_list_prepend(dt_list_t *dlp, void *new)
{
	dt_list_t *p = new;		/* p = new list element */
	dt_list_t *q = dlp->dl_next;	/* q = head list element */

	dlp->dl_next = p;
	p->dl_prev = NULL;
	p->dl_next = q;

	if (q != NULL) {
		assert(q->dl_prev == NULL);
		q->dl_prev = p;
	} else {
		assert(dlp->dl_prev == NULL);
		dlp->dl_prev = p;
	}
}