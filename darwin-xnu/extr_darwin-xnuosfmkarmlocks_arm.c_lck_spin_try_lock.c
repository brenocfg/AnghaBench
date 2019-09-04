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
struct TYPE_3__ {int /*<<< orphan*/  hwlock; } ;
typedef  TYPE_1__ lck_spin_t ;

/* Variables and functions */
 int hw_lock_try (int /*<<< orphan*/ *) ; 

int
lck_spin_try_lock(lck_spin_t *lock)
{
	return hw_lock_try(&lock->hwlock);
}