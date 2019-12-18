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
 int NR_NODE_STATES ; 
 int /*<<< orphan*/  node_class ; 
 int /*<<< orphan*/ * node_state_attr ; 
 int sysdev_class_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int node_states_init(void)
{
	int i;
	int err = 0;

	for (i = 0;  i < NR_NODE_STATES; i++) {
		int ret;
		ret = sysdev_class_create_file(&node_class, node_state_attr[i]);
		if (!err)
			err = ret;
	}
	return err;
}