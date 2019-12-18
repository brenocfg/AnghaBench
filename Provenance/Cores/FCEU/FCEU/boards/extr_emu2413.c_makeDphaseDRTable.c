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
typedef  int int32 ;

/* Variables and functions */
 int /*<<< orphan*/ ** dphaseDRTable ; 
 int /*<<< orphan*/  rate_adjust (int) ; 

__attribute__((used)) static void makeDphaseDRTable(void) {
	int32 DR, Rks, RM, RL;

	for (DR = 0; DR < 16; DR++)
		for (Rks = 0; Rks < 16; Rks++) {
			RM = DR + (Rks >> 2);
			RL = Rks & 3;
			if (RM > 15)
				RM = 15;
			switch (DR) {
			case 0:
				dphaseDRTable[DR][Rks] = 0;
				break;
			default:
				dphaseDRTable[DR][Rks] = rate_adjust((RL + 4) << (RM - 1));
				break;
			}
		}
}