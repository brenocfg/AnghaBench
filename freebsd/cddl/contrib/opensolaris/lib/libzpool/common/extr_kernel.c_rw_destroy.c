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
struct TYPE_3__ {scalar_t__ rw_count; int /*<<< orphan*/  initialized; void* rw_owner; int /*<<< orphan*/  rw_lock; } ;
typedef  TYPE_1__ krwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  rwlock_destroy (int /*<<< orphan*/ *) ; 

void
rw_destroy(krwlock_t *rwlp)
{
	ASSERT(rwlp->rw_count == 0);
	rwlock_destroy(&rwlp->rw_lock);
	rwlp->rw_owner = (void *)-1UL;
	rwlp->initialized = B_FALSE;
}