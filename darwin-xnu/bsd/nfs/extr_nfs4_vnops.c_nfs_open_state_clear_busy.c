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
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_3__ {int n_openflags; int /*<<< orphan*/  n_openlock; } ;

/* Variables and functions */
 int N_OPENBUSY ; 
 int N_OPENWANT ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
nfs_open_state_clear_busy(nfsnode_t np)
{
	int wanted;

	lck_mtx_lock(&np->n_openlock);
	if (!(np->n_openflags & N_OPENBUSY))
		panic("nfs_open_state_clear_busy");
	wanted = (np->n_openflags & N_OPENWANT);
	np->n_openflags &= ~(N_OPENBUSY|N_OPENWANT);
	lck_mtx_unlock(&np->n_openlock);
	if (wanted)
		wakeup(&np->n_openflags);
}