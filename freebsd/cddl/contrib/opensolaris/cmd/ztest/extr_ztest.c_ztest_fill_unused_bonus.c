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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_3__ {int /*<<< orphan*/ * db_data; } ;
typedef  TYPE_1__ dmu_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_P2ALIGNED (int,int) ; 
 int /*<<< orphan*/  ZTEST_BONUS_FILL_TOKEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmu_objset_id (int /*<<< orphan*/ *) ; 

void
ztest_fill_unused_bonus(dmu_buf_t *db, void *end, uint64_t obj,
    objset_t *os, uint64_t gen)
{
	uint64_t *bonusp;

	ASSERT(IS_P2ALIGNED((char *)end - (char *)db->db_data, 8));

	for (bonusp = db->db_data; bonusp < (uint64_t *)end; bonusp++) {
		uint64_t token = ZTEST_BONUS_FILL_TOKEN(obj, dmu_objset_id(os),
		    gen, bonusp - (uint64_t *)db->db_data);
		*bonusp = token;
	}
}