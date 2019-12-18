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
typedef  int /*<<< orphan*/  lck_mtx_t ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_check_preemption () ; 
 int /*<<< orphan*/  lck_mtx_lock_spin_always (int /*<<< orphan*/ *) ; 

void
lck_mtx_lock_spin(
	lck_mtx_t	*lock)
{
	lck_mtx_check_preemption();
	lck_mtx_lock_spin_always(lock);
}