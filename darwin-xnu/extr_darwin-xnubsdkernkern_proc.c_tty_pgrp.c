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
struct tty {struct pgrp* t_pgrp; } ;
struct pgrp {int pg_listflags; int /*<<< orphan*/  pg_refcount; } ;

/* Variables and functions */
 int PGRP_FLAG_DEAD ; 
 struct pgrp* PGRP_NULL ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

struct pgrp *
tty_pgrp(struct tty * tp)
{
	struct pgrp * pg = PGRP_NULL;

	proc_list_lock();
	pg = tp->t_pgrp;

	if (pg != PGRP_NULL) {
		if ((pg->pg_listflags & PGRP_FLAG_DEAD) != 0)
			panic("tty_pgrp: ref being povided for dead pgrp");
		pg->pg_refcount++;
	}
	proc_list_unlock();

	return(pg);
}