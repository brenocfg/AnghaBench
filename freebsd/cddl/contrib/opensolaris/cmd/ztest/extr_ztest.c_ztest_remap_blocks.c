#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zd_name; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  RW_READER ; 
 int dmu_objset_remap_indirects (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_name_lock ; 

void
ztest_remap_blocks(ztest_ds_t *zd, uint64_t id)
{
	rw_enter(&ztest_name_lock, RW_READER);

	int error = dmu_objset_remap_indirects(zd->zd_name);
	if (error == ENOSPC)
		error = 0;
	ASSERT0(error);

	rw_exit(&ztest_name_lock);
}