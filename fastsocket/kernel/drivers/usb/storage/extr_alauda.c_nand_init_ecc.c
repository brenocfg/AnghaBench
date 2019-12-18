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
 int* ecc2 ; 
 int* parity ; 

__attribute__((used)) static void nand_init_ecc(void) {
	int i, j, a;

	parity[0] = 0;
	for (i = 1; i < 256; i++)
		parity[i] = (parity[i&(i-1)] ^ 1);

	for (i = 0; i < 256; i++) {
		a = 0;
		for (j = 0; j < 8; j++) {
			if (i & (1<<j)) {
				if ((j & 1) == 0)
					a ^= 0x04;
				if ((j & 2) == 0)
					a ^= 0x10;
				if ((j & 4) == 0)
					a ^= 0x40;
			}
		}
		ecc2[i] = ~(a ^ (a<<1) ^ (parity[i] ? 0xa8 : 0));
	}
}