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
struct TYPE_3__ {int /*<<< orphan*/ * zd_range_lock; int /*<<< orphan*/ * zd_object_lock; int /*<<< orphan*/  zd_dirobj_lock; } ;
typedef  TYPE_1__ ztest_ds_t ;

/* Variables and functions */
 int ZTEST_OBJECT_LOCKS ; 
 int ZTEST_RANGE_LOCKS ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_rll_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ztest_zd_fini(ztest_ds_t *zd)
{
	mutex_destroy(&zd->zd_dirobj_lock);

	for (int l = 0; l < ZTEST_OBJECT_LOCKS; l++)
		ztest_rll_destroy(&zd->zd_object_lock[l]);

	for (int l = 0; l < ZTEST_RANGE_LOCKS; l++)
		ztest_rll_destroy(&zd->zd_range_lock[l]);
}