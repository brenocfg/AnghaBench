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

/* Variables and functions */
#define  TEST_MTX_LOCK_SPIN_ALWAYS_STATS 135 
#define  TEST_MTX_LOCK_SPIN_STATS 134 
#define  TEST_MTX_LOCK_STATS 133 
#define  TEST_MTX_TRY_LOCK_SPIN_ALWAYS_STATS 132 
#define  TEST_MTX_TRY_LOCK_SPIN_STATS 131 
#define  TEST_MTX_TRY_LOCK_STATS 130 
#define  TEST_MTX_UNLOCK_MTX_STATS 129 
#define  TEST_MTX_UNLOCK_SPIN_STATS 128 
 int snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
print_test_mtx_stats_string_name(
	int type_num,
	char* buffer,
	int size)
{
	char* type = "";
	switch (type_num) {
	case TEST_MTX_LOCK_STATS:
		type = "TEST_MTX_LOCK_STATS";
		break;
	case TEST_MTX_TRY_LOCK_STATS:
		type = "TEST_MTX_TRY_LOCK_STATS";
		break;
	case TEST_MTX_LOCK_SPIN_STATS:
		type = "TEST_MTX_LOCK_SPIN_STATS";
		break;
	case TEST_MTX_LOCK_SPIN_ALWAYS_STATS:
		type = "TEST_MTX_LOCK_SPIN_ALWAYS_STATS";
		break;
	case TEST_MTX_TRY_LOCK_SPIN_STATS:
		type = "TEST_MTX_TRY_LOCK_SPIN_STATS";
		break;
	case TEST_MTX_TRY_LOCK_SPIN_ALWAYS_STATS:
		type = "TEST_MTX_TRY_LOCK_SPIN_ALWAYS_STATS";
		break;
	case TEST_MTX_UNLOCK_MTX_STATS:
		type = "TEST_MTX_UNLOCK_MTX_STATS";
		break;
	case TEST_MTX_UNLOCK_SPIN_STATS:
		type = "TEST_MTX_UNLOCK_SPIN_STATS";
		break;
	default:
		break;
	}

	return snprintf(buffer, size, "%s ", type);
}