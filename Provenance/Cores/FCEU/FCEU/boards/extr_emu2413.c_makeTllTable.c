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
typedef  scalar_t__ uint32 ;
typedef  int int32 ;

/* Variables and functions */
 int EG_STEP ; 
 scalar_t__ TL2EG (int) ; 
 int dB2 (double) ; 
 scalar_t__**** tllTable ; 

__attribute__((used)) static void makeTllTable(void) {
#define dB2(x) ((x) * 2)

	static double kltable[16] = {
		dB2(0.000), dB2(9.000), dB2(12.000), dB2(13.875), dB2(15.000), dB2(16.125), dB2(16.875), dB2(17.625),
		dB2(18.000), dB2(18.750), dB2(19.125), dB2(19.500), dB2(19.875), dB2(20.250), dB2(20.625), dB2(21.000)
	};

	int32 tmp;
	int32 fnum, block, TL, KL;

	for (fnum = 0; fnum < 16; fnum++)
		for (block = 0; block < 8; block++)
			for (TL = 0; TL < 64; TL++)
				for (KL = 0; KL < 4; KL++) {
					if (KL == 0) {
						tllTable[fnum][block][TL][KL] = TL2EG(TL);
					} else {
						tmp = (int32)(kltable[fnum] - dB2(3.000) * (7 - block));
						if (tmp <= 0)
							tllTable[fnum][block][TL][KL] = TL2EG(TL);
						else
							tllTable[fnum][block][TL][KL] = (uint32)((tmp >> (3 - KL)) / EG_STEP) + TL2EG(TL);
					}
				}
}