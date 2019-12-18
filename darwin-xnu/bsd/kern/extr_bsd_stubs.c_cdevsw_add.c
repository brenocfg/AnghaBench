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
struct cdevsw {int dummy; } ;

/* Variables and functions */
 struct cdevsw* cdevsw ; 
 int cdevsw_isfree (int) ; 
 int /*<<< orphan*/  devsw_lock_list_mtx ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

int
cdevsw_add(int index, struct cdevsw * csw)
{
	lck_mtx_lock_spin(&devsw_lock_list_mtx);
	index = cdevsw_isfree(index);
	if (index < 0) {
		index = -1;
	} else {
		cdevsw[index] = *csw;
	}
	lck_mtx_unlock(&devsw_lock_list_mtx);
	return (index);
}