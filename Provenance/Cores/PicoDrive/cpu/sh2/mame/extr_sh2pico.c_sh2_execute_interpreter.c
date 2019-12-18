#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_22__ {int icount; int pending_level; int sr; int (* irq_callback ) (TYPE_1__*,int) ;scalar_t__ test_irq; scalar_t__ delay; scalar_t__ pc; scalar_t__ ppc; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */
 int RW (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  op0000 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op0001 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op0010 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op0011 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op0100 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op0101 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op0110 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op0111 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op1000 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op1001 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op1010 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op1011 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op1100 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op1101 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op1110 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  op1111 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sh2_do_irq (TYPE_1__*,int,int) ; 
 int stub1 (TYPE_1__*,int) ; 

int sh2_execute_interpreter(SH2 *sh2, int cycles)
{
	UINT32 opcode;

	sh2->icount = cycles;

	if (sh2->icount <= 0)
		goto out;

	do
	{
		if (sh2->delay)
		{
			sh2->ppc = sh2->delay;
			opcode = RW(sh2, sh2->delay);
			sh2->pc -= 2;
		}
		else
		{
			sh2->ppc = sh2->pc;
			opcode = RW(sh2, sh2->pc);
		}

		sh2->delay = 0;
		sh2->pc += 2;

		switch (opcode & ( 15 << 12))
		{
		case  0<<12: op0000(sh2, opcode); break;
		case  1<<12: op0001(sh2, opcode); break;
		case  2<<12: op0010(sh2, opcode); break;
		case  3<<12: op0011(sh2, opcode); break;
		case  4<<12: op0100(sh2, opcode); break;
		case  5<<12: op0101(sh2, opcode); break;
		case  6<<12: op0110(sh2, opcode); break;
		case  7<<12: op0111(sh2, opcode); break;
		case  8<<12: op1000(sh2, opcode); break;
		case  9<<12: op1001(sh2, opcode); break;
		case 10<<12: op1010(sh2, opcode); break;
		case 11<<12: op1011(sh2, opcode); break;
		case 12<<12: op1100(sh2, opcode); break;
		case 13<<12: op1101(sh2, opcode); break;
		case 14<<12: op1110(sh2, opcode); break;
		default: op1111(sh2, opcode); break;
		}

		sh2->icount--;

		if (sh2->test_irq && !sh2->delay && sh2->pending_level > ((sh2->sr >> 4) & 0x0f))
		{
			int level = sh2->pending_level;
			int vector = sh2->irq_callback(sh2, level);
			sh2_do_irq(sh2, level, vector);
			sh2->test_irq = 0;
		}

	}
	while (sh2->icount > 0 || sh2->delay);	/* can't interrupt before delay */

out:
	return sh2->icount;
}