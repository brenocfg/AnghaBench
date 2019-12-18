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
struct kauai_timing {int cycle_time; int /*<<< orphan*/  timing_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static inline u32
kauai_lookup_timing(struct kauai_timing* table, int cycle_time)
{
	int i;
	
	for (i=0; table[i].cycle_time; i++)
		if (cycle_time > table[i+1].cycle_time)
			return table[i].timing_reg;
	BUG();
	return 0;
}