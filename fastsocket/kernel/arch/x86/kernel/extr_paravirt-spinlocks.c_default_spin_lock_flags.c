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
typedef  int /*<<< orphan*/  raw_spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_spin_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
default_spin_lock_flags(raw_spinlock_t *lock, unsigned long flags)
{
	__raw_spin_lock(lock);
}