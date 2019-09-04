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
 scalar_t__* cdevsw_flags ; 
 int /*<<< orphan*/  devsw_lock_list_mtx ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int nchrdev ; 
 struct cdevsw nocdev ; 

int
cdevsw_remove(int index, struct cdevsw * csw)
{
	struct cdevsw * devsw;

	if (index < 0 || index >= nchrdev)
		return (-1);

	devsw = &cdevsw[index];
	lck_mtx_lock_spin(&devsw_lock_list_mtx);
	if ((memcmp((char *)devsw, (char *)csw, sizeof(struct cdevsw)) != 0)) {
		index = -1;
	} else {
		cdevsw[index] = nocdev;
		cdevsw_flags[index] = 0;
	}
	lck_mtx_unlock(&devsw_lock_list_mtx);
	return (index);
}