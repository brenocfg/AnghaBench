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

__attribute__((used)) static int nodeid_warned(int nodeid, int num_nodes, int *warned)
{
	int i;

	for (i = 0; i < num_nodes; i++) {
		if (!warned[i]) {
			warned[i] = nodeid;
			return 0;
		}
		if (warned[i] == nodeid)
			return 1;
	}
	return 0;
}