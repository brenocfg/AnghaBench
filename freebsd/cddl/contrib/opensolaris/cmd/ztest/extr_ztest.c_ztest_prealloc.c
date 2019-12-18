#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * zd_os; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  rl_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RL_READER ; 
 int /*<<< orphan*/  RL_WRITER ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  dmu_free_long_range (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_prealloc (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_write (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ztest_object_lock (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_object_unlock (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * ztest_range_lock (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_range_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ztest_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ztest_prealloc(ztest_ds_t *zd, uint64_t object, uint64_t offset, uint64_t size)
{
	objset_t *os = zd->zd_os;
	dmu_tx_t *tx;
	uint64_t txg;
	rl_t *rl;

	txg_wait_synced(dmu_objset_pool(os), 0);

	ztest_object_lock(zd, object, RL_READER);
	rl = ztest_range_lock(zd, object, offset, size, RL_WRITER);

	tx = dmu_tx_create(os);

	dmu_tx_hold_write(tx, object, offset, size);

	txg = ztest_tx_assign(tx, TXG_WAIT, FTAG);

	if (txg != 0) {
		dmu_prealloc(os, object, offset, size, tx);
		dmu_tx_commit(tx);
		txg_wait_synced(dmu_objset_pool(os), txg);
	} else {
		(void) dmu_free_long_range(os, object, offset, size);
	}

	ztest_range_unlock(rl);
	ztest_object_unlock(zd, object);
}