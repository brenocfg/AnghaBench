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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int EINVAL ; 
 int RANK_CNT_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugf0 (char*,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int numrank(u32 mtr)
{
	int ranks = (1 << RANK_CNT_BITS(mtr));

	if (ranks > 4) {
		debugf0("Invalid number of ranks: %d (max = 4) raw value = %x (%04x)",
			ranks, (unsigned int)RANK_CNT_BITS(mtr), mtr);
		return -EINVAL;
	}

	return ranks;
}