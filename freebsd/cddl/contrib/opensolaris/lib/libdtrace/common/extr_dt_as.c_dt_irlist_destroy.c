#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* di_next; } ;
typedef  TYPE_1__ dt_irnode_t ;
struct TYPE_6__ {TYPE_1__* dl_list; } ;
typedef  TYPE_2__ dt_irlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
dt_irlist_destroy(dt_irlist_t *dlp)
{
	dt_irnode_t *dip, *nip;

	for (dip = dlp->dl_list; dip != NULL; dip = nip) {
		nip = dip->di_next;
		free(dip);
	}
}