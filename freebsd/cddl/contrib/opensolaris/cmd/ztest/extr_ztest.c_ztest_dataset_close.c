#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zd_os; int /*<<< orphan*/  zd_zilog; } ;
typedef  TYPE_1__ ztest_ds_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zil_close (int /*<<< orphan*/ ) ; 
 TYPE_1__* ztest_ds ; 
 int /*<<< orphan*/  ztest_zd_fini (TYPE_1__*) ; 

__attribute__((used)) static void
ztest_dataset_close(int d)
{
	ztest_ds_t *zd = &ztest_ds[d];

	zil_close(zd->zd_zilog);
	dmu_objset_disown(zd->zd_os, zd);

	ztest_zd_fini(zd);
}