#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 TYPE_1__* ia64_psr (struct pt_regs*) ; 

int
ia32_intercept (struct pt_regs *regs, unsigned long isr)
{
	switch ((isr >> 16) & 0xff) {
	      case 0:	/* Instruction intercept fault */
	      case 4:	/* Locked Data reference fault */
	      case 1:	/* Gate intercept trap */
		return -1;

	      case 2:	/* System flag trap */
		if (((isr >> 14) & 0x3) >= 2) {
			/* MOV SS, POP SS instructions */
			ia64_psr(regs)->id = 1;
			return 0;
		} else
			return -1;
	}
	return -1;
}