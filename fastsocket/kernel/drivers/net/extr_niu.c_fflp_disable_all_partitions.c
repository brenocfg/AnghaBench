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
struct niu {int dummy; } ;

/* Variables and functions */
 unsigned long FCRAM_NUM_PARTITIONS ; 
 int fflp_set_partition (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fflp_disable_all_partitions(struct niu *np)
{
	unsigned long i;

	for (i = 0; i < FCRAM_NUM_PARTITIONS; i++) {
		int err = fflp_set_partition(np, 0, 0, 0, 0);
		if (err)
			return err;
	}
	return 0;
}