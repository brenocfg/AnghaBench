#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* gr; } ;
struct TYPE_3__ {int h; } ;

/* Variables and functions */
 int PROGRAM (int) ; 
 int SSP_A ; 
 int SSP_AL ; 
 int SSP_P ; 
 size_t SSP_PC ; 
 TYPE_2__ known_regs ; 

__attribute__((used)) static int tr_predict_al_need(void)
{
	int tmpv, tmpv2, op, pc = known_regs.gr[SSP_PC].h;

	while (1)
	{
		op = PROGRAM(pc);
		switch (op >> 9)
		{
			// ld d, s
			case 0x00:
				tmpv2 = (op >> 4) & 0xf; // dst
				tmpv  = op & 0xf; // src
				if ((tmpv2 == SSP_A && tmpv == SSP_P) || tmpv2 == SSP_AL) // ld A, P; ld AL, *
					return 0;
				break;

			// ld (ri), s
			case 0x02:
			// ld ri, s
			case 0x0a:
			// OP a, s
			case 0x10: case 0x30: case 0x40: case 0x60: case 0x70:
				tmpv  = op & 0xf; // src
				if (tmpv == SSP_AL) // OP *, AL
					return 1;
				break;

			case 0x04:
			case 0x06:
			case 0x14:
			case 0x34:
			case 0x44:
			case 0x64:
			case 0x74: pc++; break;

			// call cond, addr
			case 0x24:
			// bra cond, addr
			case 0x26:
			// mod cond, op
			case 0x48:
			// mpys?
			case 0x1b:
			// mpya (rj), (ri), b
			case 0x4b: return 1;

			// mld (rj), (ri), b
			case 0x5b: return 0; // cleared anyway

			// and A, *
			case 0x50:
				tmpv  = op & 0xf; // src
				if (tmpv == SSP_AL) return 1;
			case 0x51: case 0x53: case 0x54: case 0x55: case 0x59: case 0x5c:
				return 0;
		}
		pc++;
	}
}