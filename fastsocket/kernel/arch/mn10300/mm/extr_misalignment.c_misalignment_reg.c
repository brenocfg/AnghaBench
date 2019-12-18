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
#define  AM0 141 
#define  AM1 140 
#define  AM2 139 
 size_t* Areg_index ; 
 int /*<<< orphan*/  BUG () ; 
#define  DM0 138 
#define  DM1 137 
#define  DM2 136 
 size_t* Dreg_index ; 
#define  RD0 135 
#define  RD2 134 
 int REG_SP ; 
#define  RM0 133 
#define  RM1 132 
#define  RM2 131 
#define  RM4 130 
#define  RM6 129 
 size_t* Rreg_index ; 
#define  SP 128 

__attribute__((used)) static int misalignment_reg(unsigned long *registers, unsigned params,
			    unsigned opcode, unsigned long disp,
			    unsigned long **_register)
{
	params &= 0x7fffffff;

	if (params & 0xffffff00)
		return 0;

	switch (params & 0xff) {
	case DM0:
		*_register = &registers[Dreg_index[opcode & 0x03]];
		break;
	case DM1:
		*_register = &registers[Dreg_index[opcode >> 2 & 0x03]];
		break;
	case DM2:
		*_register = &registers[Dreg_index[opcode >> 4 & 0x03]];
		break;
	case AM0:
		*_register = &registers[Areg_index[opcode & 0x03]];
		break;
	case AM1:
		*_register = &registers[Areg_index[opcode >> 2 & 0x03]];
		break;
	case AM2:
		*_register = &registers[Areg_index[opcode >> 4 & 0x03]];
		break;
	case RM0:
		*_register = &registers[Rreg_index[opcode & 0x0f]];
		break;
	case RM1:
		*_register = &registers[Rreg_index[opcode >> 2 & 0x0f]];
		break;
	case RM2:
		*_register = &registers[Rreg_index[opcode >> 4 & 0x0f]];
		break;
	case RM4:
		*_register = &registers[Rreg_index[opcode >> 8 & 0x0f]];
		break;
	case RM6:
		*_register = &registers[Rreg_index[opcode >> 12 & 0x0f]];
		break;
	case RD0:
		*_register = &registers[Rreg_index[disp & 0x0f]];
		break;
	case RD2:
		*_register = &registers[Rreg_index[disp >> 4 & 0x0f]];
		break;
	case SP:
		*_register = &registers[REG_SP >> 2];
		break;

	default:
		BUG();
		return 0;
	}

	return 1;
}