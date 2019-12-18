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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */

int
dtrace_instr_size(uint32_t instr, int thumb_mode)
{
	if (thumb_mode) {
		uint16_t instr16 = *(uint16_t*) &instr;
		if (((instr16 >> 11) & 0x1F) > 0x1C)
			return 4;
		else
			return 2;
	} else {
		return 4;
	}
}