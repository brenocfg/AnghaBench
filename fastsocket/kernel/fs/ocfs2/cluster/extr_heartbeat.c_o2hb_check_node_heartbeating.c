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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  testing_map ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ML_HEARTBEAT ; 
 int /*<<< orphan*/  O2NM_MAX_NODES ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2hb_fill_node_map (unsigned long*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

int o2hb_check_node_heartbeating(u8 node_num)
{
	unsigned long testing_map[BITS_TO_LONGS(O2NM_MAX_NODES)];

	o2hb_fill_node_map(testing_map, sizeof(testing_map));
	if (!test_bit(node_num, testing_map)) {
		mlog(ML_HEARTBEAT,
		     "node (%u) does not have heartbeating enabled.\n",
		     node_num);
		return 0;
	}

	return 1;
}