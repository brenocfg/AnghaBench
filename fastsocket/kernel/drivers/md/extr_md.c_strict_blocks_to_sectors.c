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
typedef  unsigned long long sector_t ;
typedef  int /*<<< orphan*/  blocks ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ kstrtoull (char const*,int,unsigned long long*) ; 

__attribute__((used)) static int strict_blocks_to_sectors(const char *buf, sector_t *sectors)
{
	unsigned long long blocks;
	sector_t new;

	if (kstrtoull(buf, 10, &blocks) < 0)
		return -EINVAL;

	if (blocks & 1ULL << (8 * sizeof(blocks) - 1))
		return -EINVAL; /* sector conversion overflow */

	new = blocks * 2;
	if (new != blocks * 2)
		return -EINVAL; /* unsigned long long to sector_t overflow */

	*sectors = new;
	return 0;
}