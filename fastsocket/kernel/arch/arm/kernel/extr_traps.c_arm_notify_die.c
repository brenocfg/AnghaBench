#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct siginfo {int /*<<< orphan*/  si_signo; } ;
struct pt_regs {int dummy; } ;
struct TYPE_4__ {unsigned long error_code; unsigned long trap_no; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  die (char const*,struct pt_regs*,unsigned long) ; 
 int /*<<< orphan*/  force_sig_info (int /*<<< orphan*/ ,struct siginfo*,TYPE_2__*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void arm_notify_die(const char *str, struct pt_regs *regs,
		struct siginfo *info, unsigned long err, unsigned long trap)
{
	if (user_mode(regs)) {
		current->thread.error_code = err;
		current->thread.trap_no = trap;

		force_sig_info(info->si_signo, info, current);
	} else {
		die(str, regs, err);
	}
}