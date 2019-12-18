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
struct pt_regs {int cp0_status; } ;

/* Variables and functions */
 int ST0_FR ; 
 int /*<<< orphan*/  TIF_32BIT_REGS ; 
 scalar_t__ cpu_has_fpu ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cop1_64bit(struct pt_regs *xcp)
{
	if (cpu_has_fpu)
		return xcp->cp0_status & ST0_FR;
#ifdef CONFIG_64BIT
	return !test_thread_flag(TIF_32BIT_REGS);
#else
	return 0;
#endif
}