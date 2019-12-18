#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ od_object; } ;
typedef  TYPE_1__ ztest_od_t ;
struct TYPE_8__ {int /*<<< orphan*/ * zd_os; } ;
typedef  TYPE_2__ ztest_ds_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  od ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OT_ZAP_OTHER ; 
 int EEXIST ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  TXG_MIGHTWAIT ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_zap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__,scalar_t__) ; 
 int zap_add (int /*<<< orphan*/ *,scalar_t__,char*,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ztest_object_init (TYPE_2__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ztest_od_init (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_random (int) ; 
 scalar_t__ ztest_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ztest_fzap(ztest_ds_t *zd, uint64_t id)
{
	objset_t *os = zd->zd_os;
	ztest_od_t od[1];
	uint64_t object, txg;

	ztest_od_init(&od[0], id, FTAG, 0, DMU_OT_ZAP_OTHER, 0, 0, 0);

	if (ztest_object_init(zd, od, sizeof (od), !ztest_random(2)) != 0)
		return;

	object = od[0].od_object;

	/*
	 * Add entries to this ZAP and make sure it spills over
	 * and gets upgraded to a fatzap. Also, since we are adding
	 * 2050 entries we should see ptrtbl growth and leaf-block split.
	 */
	for (int i = 0; i < 2050; i++) {
		char name[ZFS_MAX_DATASET_NAME_LEN];
		uint64_t value = i;
		dmu_tx_t *tx;
		int error;

		(void) snprintf(name, sizeof (name), "fzap-%llu-%llu",
		    id, value);

		tx = dmu_tx_create(os);
		dmu_tx_hold_zap(tx, object, B_TRUE, name);
		txg = ztest_tx_assign(tx, TXG_MIGHTWAIT, FTAG);
		if (txg == 0)
			return;
		error = zap_add(os, object, name, sizeof (uint64_t), 1,
		    &value, tx);
		ASSERT(error == 0 || error == EEXIST);
		dmu_tx_commit(tx);
	}
}