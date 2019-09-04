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
struct TYPE_3__ {int /*<<< orphan*/  spin_lock; } ;
typedef  TYPE_1__ SL_LOCK ;
typedef  int /*<<< orphan*/  NDIS_SPIN_LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  NdisAcquireSpinLock (int /*<<< orphan*/ *) ; 

void SlLock(SL_LOCK *lock)
{
	NDIS_SPIN_LOCK *spin_lock;
	// Validate arguments
	if (lock == NULL)
	{
		return;
	}

	spin_lock = &lock->spin_lock;
	NdisAcquireSpinLock(spin_lock);
}