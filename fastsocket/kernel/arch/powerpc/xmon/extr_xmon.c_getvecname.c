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

__attribute__((used)) static
const char *getvecname(unsigned long vec)
{
	char *ret;

	switch (vec) {
	case 0x100:	ret = "(System Reset)"; break;
	case 0x200:	ret = "(Machine Check)"; break;
	case 0x300:	ret = "(Data Access)"; break;
	case 0x380:	ret = "(Data SLB Access)"; break;
	case 0x400:	ret = "(Instruction Access)"; break;
	case 0x480:	ret = "(Instruction SLB Access)"; break;
	case 0x500:	ret = "(Hardware Interrupt)"; break;
	case 0x600:	ret = "(Alignment)"; break;
	case 0x700:	ret = "(Program Check)"; break;
	case 0x800:	ret = "(FPU Unavailable)"; break;
	case 0x900:	ret = "(Decrementer)"; break;
	case 0xc00:	ret = "(System Call)"; break;
	case 0xd00:	ret = "(Single Step)"; break;
	case 0xf00:	ret = "(Performance Monitor)"; break;
	case 0xf20:	ret = "(Altivec Unavailable)"; break;
	case 0x1300:	ret = "(Instruction Breakpoint)"; break;
	default: ret = "";
	}
	return ret;
}