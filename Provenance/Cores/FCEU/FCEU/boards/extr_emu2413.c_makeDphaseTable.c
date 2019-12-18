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
typedef  int uint32 ;

/* Variables and functions */
 int DP_BITS ; 
 int /*<<< orphan*/ *** dphaseTable ; 
 int /*<<< orphan*/  rate_adjust (int) ; 

__attribute__((used)) static void makeDphaseTable(void) {
	uint32 fnum, block, ML;
	uint32 mltable[16] =
	{ 1, 1 * 2, 2 * 2, 3 * 2, 4 * 2, 5 * 2, 6 * 2, 7 * 2, 8 * 2, 9 * 2, 10 * 2, 10 * 2, 12 * 2, 12 * 2, 15 * 2, 15 * 2 };

	for (fnum = 0; fnum < 512; fnum++)
		for (block = 0; block < 8; block++)
			for (ML = 0; ML < 16; ML++)
				dphaseTable[fnum][block][ML] = rate_adjust(((fnum * mltable[ML]) << block) >> (20 - DP_BITS));
}