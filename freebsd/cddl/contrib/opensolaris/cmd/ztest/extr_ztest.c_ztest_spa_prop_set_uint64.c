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
typedef  int /*<<< orphan*/  zpool_prop_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int spa_prop_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_record_enospc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ztest_spa ; 

__attribute__((used)) static int
ztest_spa_prop_set_uint64(zpool_prop_t prop, uint64_t value)
{
	spa_t *spa = ztest_spa;
	nvlist_t *props = NULL;
	int error;

	VERIFY(nvlist_alloc(&props, NV_UNIQUE_NAME, 0) == 0);
	VERIFY(nvlist_add_uint64(props, zpool_prop_to_name(prop), value) == 0);

	error = spa_prop_set(spa, props);

	nvlist_free(props);

	if (error == ENOSPC) {
		ztest_record_enospc(FTAG);
		return (error);
	}
	ASSERT0(error);

	return (error);
}