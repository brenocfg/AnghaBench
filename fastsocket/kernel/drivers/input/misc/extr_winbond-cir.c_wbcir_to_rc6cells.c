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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static u8
wbcir_to_rc6cells(u8 val)
{
	u8 coded = 0x00;
	int i;

	val &= 0x0F;
	for (i = 0; i < 4; i++) {
		if (val & 0x01)
			coded |= 0x02 << (i * 2);
		else
			coded |= 0x01 << (i * 2);
		val >>= 1;
	}

	return coded;
}