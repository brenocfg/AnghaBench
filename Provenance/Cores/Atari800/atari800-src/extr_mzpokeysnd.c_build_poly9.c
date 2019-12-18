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
 unsigned char* poly9tbl ; 

__attribute__((used)) static void build_poly9(void)
{
	unsigned int c;
	unsigned int i;
	unsigned int poly9 = 1;

	for(i = 0; i < 511; i++) {
		poly9tbl[i] = (unsigned char) poly9;
		c = ((poly9 >> 3) ^ (poly9 >> 8)) & 1;
		poly9 = ((poly9 << 1) & 511) + c;
	}
}