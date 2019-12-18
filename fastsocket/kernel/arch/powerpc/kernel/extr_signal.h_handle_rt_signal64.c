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
struct pt_regs {int dummy; } ;
struct k_sigaction {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int EFAULT ; 

__attribute__((used)) static inline int handle_rt_signal64(int signr, struct k_sigaction *ka,
				     siginfo_t *info, sigset_t *set,
				     struct pt_regs *regs)
{
	return -EFAULT;
}