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
 size_t IN_BIND_OFFS (int,int) ; 
 int /*<<< orphan*/  IN_CFG_BIND_COUNT ; 
 int /*<<< orphan*/  in_get_config (int,int /*<<< orphan*/ ,int*) ; 
 int* in_get_dev_binds (int) ; 

__attribute__((used)) static int count_bound_keys(int dev_id, int action_mask, int bindtype)
{
	const int *binds;
	int k, keys = 0;
	int count = 0;

	binds = in_get_dev_binds(dev_id);
	if (binds == NULL)
		return 0;

	in_get_config(dev_id, IN_CFG_BIND_COUNT, &count);
	for (k = 0; k < count; k++)
	{
		if (binds[IN_BIND_OFFS(k, bindtype)] & action_mask)
			keys++;
	}

	return keys;
}