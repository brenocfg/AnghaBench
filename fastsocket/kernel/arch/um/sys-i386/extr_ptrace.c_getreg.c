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
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
#define  CS 133 
#define  DS 132 
#define  ES 131 
#define  FS 130 
#define  GS 129 
 unsigned long PT_REG (int /*<<< orphan*/ *,int) ; 
#define  SS 128 

unsigned long getreg(struct task_struct *child, int regno)
{
	unsigned long retval = ~0UL;

	regno >>= 2;
	switch (regno) {
	case FS:
	case GS:
	case DS:
	case ES:
	case SS:
	case CS:
		retval = 0xffff;
		/* fall through */
	default:
		retval &= PT_REG(&child->thread.regs, regno);
	}
	return retval;
}