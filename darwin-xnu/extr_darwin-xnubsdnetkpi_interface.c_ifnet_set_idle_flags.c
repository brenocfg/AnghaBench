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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ifnet_lock_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_set_idle_flags_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 

errno_t
ifnet_set_idle_flags(ifnet_t ifp, u_int32_t new_flags, u_int32_t mask)
{
	errno_t err;

	lck_mtx_lock(rnh_lock);
	ifnet_lock_exclusive(ifp);
	err = ifnet_set_idle_flags_locked(ifp, new_flags, mask);
	ifnet_lock_done(ifp);
	lck_mtx_unlock(rnh_lock);

	return (err);
}