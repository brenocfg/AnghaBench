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
 int* memregs ; 

__attribute__((used)) static int in_gp2x_get_mmsp2_bits(void)
{
	int value;
	value = memregs[0x1198>>1] & 0xff; // GPIO M
	if (value == 0xFD) value = 0xFA;
	if (value == 0xF7) value = 0xEB;
	if (value == 0xDF) value = 0xAF;
	if (value == 0x7F) value = 0xBE;
	value |= memregs[0x1184>>1] & 0xFF00; // GPIO C
	value |= memregs[0x1186>>1] << 16; // GPIO D
	value = ~value & 0x08c0ff55;

	return value;
}