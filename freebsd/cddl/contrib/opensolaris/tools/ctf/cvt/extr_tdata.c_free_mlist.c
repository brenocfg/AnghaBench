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
struct TYPE_5__ {TYPE_2__* t_members; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_6__ {struct TYPE_6__* ml_name; struct TYPE_6__* ml_next; } ;
typedef  TYPE_2__ mlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void
free_mlist(tdesc_t *tdp)
{
	mlist_t *ml = tdp->t_members;
	mlist_t *oml;

	while (ml) {
		oml = ml;
		ml = ml->ml_next;

		if (oml->ml_name)
			free(oml->ml_name);
		free(oml);
	}
}