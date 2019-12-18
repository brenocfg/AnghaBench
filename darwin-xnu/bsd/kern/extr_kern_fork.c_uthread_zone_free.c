#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
struct doc_tombstone {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  uu_rethrottle_lock; int /*<<< orphan*/ * t_tombstone; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lck_spin_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rethrottle_lock_grp ; 
 int /*<<< orphan*/  uthread_cleanup_name (void*) ; 
 int /*<<< orphan*/  uthread_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,void*) ; 

void
uthread_zone_free(void *uthread)
{
	uthread_t uth = (uthread_t)uthread;

	if (uth->t_tombstone) {
		kfree(uth->t_tombstone, sizeof(struct doc_tombstone));
		uth->t_tombstone = NULL;
	}

	lck_spin_destroy(&uth->uu_rethrottle_lock, rethrottle_lock_grp);

	uthread_cleanup_name(uthread);
	/* and free the uthread itself */
	zfree(uthread_zone, uthread);
}