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
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ null_hashlck_grp ; 

int
nullfs_destroy_lck(lck_mtx_t * lck)
{
	int error = 1;
	if (lck && null_hashlck_grp) {
		lck_mtx_destroy(lck, null_hashlck_grp);
		error = 0;
	}
	return error;
}