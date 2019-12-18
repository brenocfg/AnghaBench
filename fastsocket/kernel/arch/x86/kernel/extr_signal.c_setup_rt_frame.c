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
struct TYPE_2__ {int sa_flags; } ;
struct k_sigaction {TYPE_1__ sa; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int EFAULT ; 
 int SA_SIGINFO ; 
 int __setup_rt_frame (int,struct k_sigaction*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pt_regs*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  force_sigsegv (int,int /*<<< orphan*/ ) ; 
 int ia32_setup_frame (int,struct k_sigaction*,int /*<<< orphan*/ *,struct pt_regs*) ; 
 int ia32_setup_rt_frame (int,struct k_sigaction*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pt_regs*) ; 
 scalar_t__ is_ia32 ; 
 int signr_convert (int) ; 

__attribute__((used)) static int
setup_rt_frame(int sig, struct k_sigaction *ka, siginfo_t *info,
	       sigset_t *set, struct pt_regs *regs)
{
	int usig = signr_convert(sig);
	int ret;

	/* Set up the stack frame */
	if (is_ia32) {
		if (ka->sa.sa_flags & SA_SIGINFO)
			ret = ia32_setup_rt_frame(usig, ka, info, set, regs);
		else
			ret = ia32_setup_frame(usig, ka, set, regs);
	} else
		ret = __setup_rt_frame(sig, ka, info, set, regs);

	if (ret) {
		force_sigsegv(sig, current);
		return -EFAULT;
	}

	return ret;
}