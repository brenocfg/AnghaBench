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
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ null_hashlck_attr ; 
 scalar_t__ null_hashlck_grp ; 

int
nullfs_init_lck(lck_mtx_t * lck)
{
	int error = 1;
	if (lck && null_hashlck_grp && null_hashlck_attr) {
		lck_mtx_init(lck, null_hashlck_grp, null_hashlck_attr);
		error = 0;
	}
	return error;
}