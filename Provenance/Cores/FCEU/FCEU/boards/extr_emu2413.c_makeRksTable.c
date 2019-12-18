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
 int*** rksTable ; 

__attribute__((used)) static void makeRksTable(void) {
	int32 fnum8, block, KR;

	for (fnum8 = 0; fnum8 < 2; fnum8++)
		for (block = 0; block < 8; block++)
			for (KR = 0; KR < 2; KR++) {
				if (KR != 0)
					rksTable[fnum8][block][KR] = (block << 1) + fnum8;
				else
					rksTable[fnum8][block][KR] = block >> 1;
			}
}