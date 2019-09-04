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
typedef  int /*<<< orphan*/  LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  KS_CURRENT_LOCK_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_NEWLOCK_COUNT ; 
 int /*<<< orphan*/ * NewLockMain () ; 

LOCK *NewLock()
{
	LOCK *lock = NewLockMain();

	// KS
	KS_INC(KS_NEWLOCK_COUNT);
	KS_INC(KS_CURRENT_LOCK_COUNT);

	return lock;
}