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
struct dquot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dq_unlock_internal (struct dquot*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quota_list_mtx_lock ; 

void
dqunlock(struct dquot *dq) {

	lck_mtx_lock(quota_list_mtx_lock);

	dq_unlock_internal(dq);

	lck_mtx_unlock(quota_list_mtx_lock);
}