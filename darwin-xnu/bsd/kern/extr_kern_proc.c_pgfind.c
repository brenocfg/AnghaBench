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
struct pgrp {int pg_listflags; int /*<<< orphan*/  pg_refcount; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int PGRP_FLAG_TERMINATE ; 
 struct pgrp* PGRP_NULL ; 
 struct pgrp* pgfind_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

struct pgrp *
pgfind(pid_t pgid)
{
	struct pgrp * pgrp;

	proc_list_lock();
	pgrp = pgfind_internal(pgid);
	if ((pgrp == NULL) || ((pgrp->pg_listflags & PGRP_FLAG_TERMINATE) != 0))
		pgrp = PGRP_NULL;
	else
		pgrp->pg_refcount++;
	proc_list_unlock();
	return(pgrp);
}