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
 unsigned char* poly5tbl ; 

__attribute__((used)) static void build_poly5(void)
{
	unsigned char c;
	unsigned char i;
	unsigned char poly5 = 1;

	for(i = 0; i < 31; i++) {
		poly5tbl[i] = ~poly5; /* Inversion! Attention! */
		c = ((poly5 >> 2) ^ (poly5 >> 4)) & 1;
		poly5 = ((poly5 << 1) & 31) + c;
	}
}