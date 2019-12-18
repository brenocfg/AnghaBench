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
struct siginfo {int si_errno; int /*<<< orphan*/  si_signo; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGSWI ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  send_sig_info (int /*<<< orphan*/ ,struct siginfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arthur_lcall7(int nr, struct pt_regs *regs)
{
	struct siginfo info;
	info.si_signo = SIGSWI;
	info.si_errno = nr;
	/* Bounce it to the emulator */
	send_sig_info(SIGSWI, &info, current);
}