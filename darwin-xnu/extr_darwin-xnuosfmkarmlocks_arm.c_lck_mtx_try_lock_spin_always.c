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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  lck_mtx_try_lock_spin_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

boolean_t
lck_mtx_try_lock_spin_always(lck_mtx_t *lock)
{
	return lck_mtx_try_lock_spin_internal(lock, FALSE);
}