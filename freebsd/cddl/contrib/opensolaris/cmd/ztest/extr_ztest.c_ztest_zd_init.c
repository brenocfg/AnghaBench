#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ zd_seq; } ;
typedef  TYPE_1__ ztest_shared_ds_t ;
struct TYPE_6__ {int /*<<< orphan*/ * zd_range_lock; int /*<<< orphan*/ * zd_object_lock; int /*<<< orphan*/  zd_dirobj_lock; int /*<<< orphan*/  zd_zilog_lock; TYPE_1__* zd_shared; int /*<<< orphan*/  zd_name; int /*<<< orphan*/  zd_zilog; int /*<<< orphan*/ * zd_os; } ;
typedef  TYPE_2__ ztest_ds_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  USYNC_THREAD ; 
 int ZTEST_OBJECT_LOCKS ; 
 int ZTEST_RANGE_LOCKS ; 
 int /*<<< orphan*/  dmu_objset_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_zil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_rll_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ztest_zd_init(ztest_ds_t *zd, ztest_shared_ds_t *szd, objset_t *os)
{
	zd->zd_os = os;
	zd->zd_zilog = dmu_objset_zil(os);
	zd->zd_shared = szd;
	dmu_objset_name(os, zd->zd_name);

	if (zd->zd_shared != NULL)
		zd->zd_shared->zd_seq = 0;

	rw_init(&zd->zd_zilog_lock, NULL, USYNC_THREAD, NULL);
	mutex_init(&zd->zd_dirobj_lock, NULL, USYNC_THREAD, NULL);

	for (int l = 0; l < ZTEST_OBJECT_LOCKS; l++)
		ztest_rll_init(&zd->zd_object_lock[l]);

	for (int l = 0; l < ZTEST_RANGE_LOCKS; l++)
		ztest_rll_init(&zd->zd_range_lock[l]);
}