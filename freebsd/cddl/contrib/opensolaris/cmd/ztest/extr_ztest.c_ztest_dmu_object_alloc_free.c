#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  od_object; } ;
typedef  TYPE_1__ ztest_od_t ;
typedef  int /*<<< orphan*/  ztest_ds_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  od ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OT_UINT64_OTHER ; 
 int /*<<< orphan*/  FTAG ; 
 size_t SPA_MAXBLOCKSHIFT ; 
 int ZTEST_RANGE_LOCKS ; 
 int /*<<< orphan*/  ztest_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ztest_object_init (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_od_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ztest_random (int) ; 

void
ztest_dmu_object_alloc_free(ztest_ds_t *zd, uint64_t id)
{
	ztest_od_t od[4];
	int batchsize = sizeof (od) / sizeof (od[0]);

	for (int b = 0; b < batchsize; b++) {
		ztest_od_init(&od[b], id, FTAG, b, DMU_OT_UINT64_OTHER,
		    0, 0, 0);
	}

	/*
	 * Destroy the previous batch of objects, create a new batch,
	 * and do some I/O on the new objects.
	 */
	if (ztest_object_init(zd, od, sizeof (od), B_TRUE) != 0)
		return;

	while (ztest_random(4 * batchsize) != 0)
		ztest_io(zd, od[ztest_random(batchsize)].od_object,
		    ztest_random(ZTEST_RANGE_LOCKS) << SPA_MAXBLOCKSHIFT);
}