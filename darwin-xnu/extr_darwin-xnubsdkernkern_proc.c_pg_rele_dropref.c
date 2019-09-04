#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pgrp {int pg_refcount; int pg_listflags; } ;

/* Variables and functions */
 int PGRP_FLAG_TERMINATE ; 
 int /*<<< orphan*/  pgdelete_dropref (struct pgrp*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

void
pg_rele_dropref(struct pgrp * pgrp)
{
	proc_list_lock();
	if ((pgrp->pg_refcount == 1) && ((pgrp->pg_listflags & PGRP_FLAG_TERMINATE) == PGRP_FLAG_TERMINATE)) {
		proc_list_unlock();
		pgdelete_dropref(pgrp);
		return;
	}

	pgrp->pg_refcount--;
	proc_list_unlock();
}