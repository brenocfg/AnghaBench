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
#define  CS 136 
#define  DS 135 
#define  EFLAGS 134 
 int EIO ; 
#define  ES 133 
 unsigned long FLAG_MASK ; 
#define  FS 132 
#define  FS_BASE 131 
#define  GS 130 
#define  GS_BASE 129 
 unsigned long PT_REGS_EFLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PT_REGS_SET (int /*<<< orphan*/ *,int,unsigned long) ; 
#define  SS 128 
 int /*<<< orphan*/  TIF_IA32 ; 
 scalar_t__ test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

int putreg(struct task_struct *child, int regno, unsigned long value)
{
	unsigned long tmp;

#ifdef TIF_IA32
	/*
	 * Some code in the 64bit emulation may not be 64bit clean.
	 * Don't take any chances.
	 */
	if (test_tsk_thread_flag(child, TIF_IA32))
		value &= 0xffffffff;
#endif
	switch (regno) {
	case FS:
	case GS:
	case DS:
	case ES:
	case SS:
	case CS:
		if (value && (value & 3) != 3)
			return -EIO;
		value &= 0xffff;
		break;

	case FS_BASE:
	case GS_BASE:
		if (!((value >> 48) == 0 || (value >> 48) == 0xffff))
			return -EIO;
		break;

	case EFLAGS:
		value &= FLAG_MASK;
		tmp = PT_REGS_EFLAGS(&child->thread.regs) & ~FLAG_MASK;
		value |= tmp;
		break;
	}

	PT_REGS_SET(&child->thread.regs, regno, value);
	return 0;
}