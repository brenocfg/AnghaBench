#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sr; int* r; int pc; int icount; scalar_t__ vbr; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */
 int I ; 
 int p32x_sh2_read32 (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  p32x_sh2_write32 (int,int,TYPE_1__*) ; 

void sh2_do_irq(SH2 *sh2, int level, int vector)
{
	sh2->sr &= 0x3f3;

	sh2->r[15] -= 4;
	p32x_sh2_write32(sh2->r[15], sh2->sr, sh2);	/* push SR onto stack */
	sh2->r[15] -= 4;
	p32x_sh2_write32(sh2->r[15], sh2->pc, sh2);	/* push PC onto stack */

	/* set I flags in SR */
	sh2->sr = (sh2->sr & ~I) | (level << 4);

	/* fetch PC */
	sh2->pc = p32x_sh2_read32(sh2->vbr + vector * 4, sh2);

	/* 13 cycles at best */
	sh2->icount -= 13;
}