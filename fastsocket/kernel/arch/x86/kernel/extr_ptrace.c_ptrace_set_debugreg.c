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
struct TYPE_2__ {unsigned long debugreg0; unsigned long debugreg1; unsigned long debugreg2; unsigned long debugreg3; unsigned long debugreg6; unsigned long debugreg7; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned long DR7_MASK ; 
 unsigned long DR_CONTROL_RESERVED ; 
 int EIO ; 
 int /*<<< orphan*/  TIF_DEBUG ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 unsigned long debugreg_addr_limit (struct task_struct*) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ptrace_set_debugreg(struct task_struct *child,
			       int n, unsigned long data)
{
	int i;

	if (unlikely(n == 4 || n == 5))
		return -EIO;

	if (n < 4 && unlikely(data >= debugreg_addr_limit(child)))
		return -EIO;

	switch (n) {
	case 0:		child->thread.debugreg0 = data; break;
	case 1:		child->thread.debugreg1 = data; break;
	case 2:		child->thread.debugreg2 = data; break;
	case 3:		child->thread.debugreg3 = data; break;

	case 6:
		if ((data & ~0xffffffffUL) != 0)
			return -EIO;
		child->thread.debugreg6 = data;
		break;

	case 7:
		/*
		 * Sanity-check data. Take one half-byte at once with
		 * check = (val >> (16 + 4*i)) & 0xf. It contains the
		 * R/Wi and LENi bits; bits 0 and 1 are R/Wi, and bits
		 * 2 and 3 are LENi. Given a list of invalid values,
		 * we do mask |= 1 << invalid_value, so that
		 * (mask >> check) & 1 is a correct test for invalid
		 * values.
		 *
		 * R/Wi contains the type of the breakpoint /
		 * watchpoint, LENi contains the length of the watched
		 * data in the watchpoint case.
		 *
		 * The invalid values are:
		 * - LENi == 0x10 (undefined), so mask |= 0x0f00.	[32-bit]
		 * - R/Wi == 0x10 (break on I/O reads or writes), so
		 *   mask |= 0x4444.
		 * - R/Wi == 0x00 && LENi != 0x00, so we have mask |=
		 *   0x1110.
		 *
		 * Finally, mask = 0x0f00 | 0x4444 | 0x1110 == 0x5f54.
		 *
		 * See the Intel Manual "System Programming Guide",
		 * 15.2.4
		 *
		 * Note that LENi == 0x10 is defined on x86_64 in long
		 * mode (i.e. even for 32-bit userspace software, but
		 * 64-bit kernel), so the x86_64 mask value is 0x5454.
		 * See the AMD manual no. 24593 (AMD64 System Programming)
		 */
#ifdef CONFIG_X86_32
#define	DR7_MASK	0x5f54
#else
#define	DR7_MASK	0x5554
#endif
		data &= ~DR_CONTROL_RESERVED;
		for (i = 0; i < 4; i++)
			if ((DR7_MASK >> ((data >> (16 + 4*i)) & 0xf)) & 1)
				return -EIO;
		child->thread.debugreg7 = data;
		if (data)
			set_tsk_thread_flag(child, TIF_DEBUG);
		else
			clear_tsk_thread_flag(child, TIF_DEBUG);
		break;
	}

	return 0;
}