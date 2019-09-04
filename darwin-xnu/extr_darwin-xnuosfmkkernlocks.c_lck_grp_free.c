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
typedef  int /*<<< orphan*/  queue_entry_t ;
typedef  int /*<<< orphan*/  lck_grp_t ;

/* Variables and functions */
 int /*<<< orphan*/  lck_grp_cnt ; 
 int /*<<< orphan*/  lck_grp_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_lock ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remque (int /*<<< orphan*/ ) ; 

void
lck_grp_free(
	lck_grp_t	*grp)
{
	lck_mtx_lock(&lck_grp_lock);
	lck_grp_cnt--;
	(void)remque((queue_entry_t)grp);
	lck_mtx_unlock(&lck_grp_lock);
	lck_grp_deallocate(grp);
}