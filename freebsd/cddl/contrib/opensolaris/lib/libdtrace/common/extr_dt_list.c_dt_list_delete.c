#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* dl_prev; TYPE_1__* dl_next; } ;
typedef  TYPE_3__ dt_list_t ;
struct TYPE_6__ {TYPE_1__* dl_next; } ;
struct TYPE_5__ {TYPE_2__* dl_prev; } ;

/* Variables and functions */

void
dt_list_delete(dt_list_t *dlp, void *existing)
{
	dt_list_t *p = existing;

	if (p->dl_prev != NULL)
		p->dl_prev->dl_next = p->dl_next;
	else
		dlp->dl_next = p->dl_next;

	if (p->dl_next != NULL)
		p->dl_next->dl_prev = p->dl_prev;
	else
		dlp->dl_prev = p->dl_prev;
}