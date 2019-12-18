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
typedef  scalar_t__ int8_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
#define  AM0 153 
#define  AM1 152 
#define  AM2 151 
 size_t* Areg_index ; 
 int /*<<< orphan*/  BUG () ; 
#define  DM0 150 
#define  DM1 149 
#define  DM2 148 
 size_t* Dreg_index ; 
#define  IMM16 147 
#define  IMM24 146 
#define  IMM32 145 
#define  IMM32_HIGH8 144 
#define  IMM32_HIGH8_MEM 143 
#define  IMM32_MEM 142 
#define  IMM8 141 
#define  RD0 140 
#define  RD2 139 
#define  RM0 138 
#define  RM1 137 
#define  RM2 136 
#define  RM4 135 
#define  RM6 134 
 size_t* Rreg_index ; 
#define  SD16 133 
#define  SD24 132 
#define  SD8 131 
#define  SIMM4_2 130 
#define  SIMM8 129 
#define  SP 128 
 int /*<<< orphan*/  kdebug (char*,...) ; 

__attribute__((used)) static int misalignment_addr(unsigned long *registers, unsigned long sp,
			     unsigned params, unsigned opcode,
			     unsigned long disp,
			     void **_address, unsigned long **_postinc,
			     unsigned long *_inc)
{
	unsigned long *postinc = NULL, address = 0, tmp;

	if (!(params & 0x1000000)) {
		kdebug("noinc");
		*_inc = 0;
		_inc = NULL;
	}

	params &= 0x00ffffff;

	do {
		switch (params & 0xff) {
		case DM0:
			postinc = &registers[Dreg_index[opcode & 0x03]];
			address += *postinc;
			break;
		case DM1:
			postinc = &registers[Dreg_index[opcode >> 2 & 0x03]];
			address += *postinc;
			break;
		case DM2:
			postinc = &registers[Dreg_index[opcode >> 4 & 0x03]];
			address += *postinc;
			break;
		case AM0:
			postinc = &registers[Areg_index[opcode & 0x03]];
			address += *postinc;
			break;
		case AM1:
			postinc = &registers[Areg_index[opcode >> 2 & 0x03]];
			address += *postinc;
			break;
		case AM2:
			postinc = &registers[Areg_index[opcode >> 4 & 0x03]];
			address += *postinc;
			break;
		case RM0:
			postinc = &registers[Rreg_index[opcode & 0x0f]];
			address += *postinc;
			break;
		case RM1:
			postinc = &registers[Rreg_index[opcode >> 2 & 0x0f]];
			address += *postinc;
			break;
		case RM2:
			postinc = &registers[Rreg_index[opcode >> 4 & 0x0f]];
			address += *postinc;
			break;
		case RM4:
			postinc = &registers[Rreg_index[opcode >> 8 & 0x0f]];
			address += *postinc;
			break;
		case RM6:
			postinc = &registers[Rreg_index[opcode >> 12 & 0x0f]];
			address += *postinc;
			break;
		case RD0:
			postinc = &registers[Rreg_index[disp & 0x0f]];
			address += *postinc;
			break;
		case RD2:
			postinc = &registers[Rreg_index[disp >> 4 & 0x0f]];
			address += *postinc;
			break;
		case SP:
			address += sp;
			break;

			/* displacements are either to be added to the address
			 * before use, or, in the case of post-inc addressing,
			 * to be added into the base register after use */
		case SD8:
		case SIMM8:
			disp = (long) (int8_t) (disp & 0xff);
			goto displace_or_inc;
		case SD16:
			disp = (long) (int16_t) (disp & 0xffff);
			goto displace_or_inc;
		case SD24:
			tmp = disp << 8;
			asm("asr 8,%0" : "=r"(tmp) : "0"(tmp));
			disp = (long) tmp;
			goto displace_or_inc;
		case SIMM4_2:
			tmp = opcode >> 4 & 0x0f;
			tmp <<= 28;
			asm("asr 28,%0" : "=r"(tmp) : "0"(tmp));
			disp = (long) tmp;
			goto displace_or_inc;
		case IMM8:
			disp &= 0x000000ff;
			goto displace_or_inc;
		case IMM16:
			disp &= 0x0000ffff;
			goto displace_or_inc;
		case IMM24:
			disp &= 0x00ffffff;
			goto displace_or_inc;
		case IMM32:
		case IMM32_MEM:
		case IMM32_HIGH8:
		case IMM32_HIGH8_MEM:
		displace_or_inc:
			kdebug("%s %lx", _inc ? "incr" : "disp", disp);
			if (!_inc)
				address += disp;
			else
				*_inc = disp;
			break;
		default:
			BUG();
			return 0;
		}
	} while ((params >>= 8));

	*_address = (void *) address;
	*_postinc = postinc;
	return 1;
}