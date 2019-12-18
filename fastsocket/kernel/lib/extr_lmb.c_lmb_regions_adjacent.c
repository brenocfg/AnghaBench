#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct lmb_region {TYPE_1__* region; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 long lmb_addrs_adjacent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long lmb_regions_adjacent(struct lmb_region *rgn,
		unsigned long r1, unsigned long r2)
{
	u64 base1 = rgn->region[r1].base;
	u64 size1 = rgn->region[r1].size;
	u64 base2 = rgn->region[r2].base;
	u64 size2 = rgn->region[r2].size;

	return lmb_addrs_adjacent(base1, size1, base2, size2);
}