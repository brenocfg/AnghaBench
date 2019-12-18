#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct siginfo {scalar_t__ si_signo; int /*<<< orphan*/  si_int; int /*<<< orphan*/  si_code; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_7__ {int ext_params; } ;
struct TYPE_5__ {scalar_t__ ri_signum; int /*<<< orphan*/  ri_cb; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int CPU_MF_INT_RI_BUF_FULL ; 
 int CPU_MF_INT_RI_HALTED ; 
 int CPU_MF_INT_RI_MASK ; 
 int /*<<< orphan*/  ECANCELED ; 
 int /*<<< orphan*/  ENOBUFS ; 
 TYPE_4__ S390_lowcore ; 
 scalar_t__ SIGRTMAX ; 
 scalar_t__ SIGRTMIN ; 
 int /*<<< orphan*/  SI_QUEUE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  memset (struct siginfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_sig_info (scalar_t__,struct siginfo*,TYPE_2__*) ; 

__attribute__((used)) static void runtime_instr_int_handler(__u16 ext_code)
{
	struct siginfo info;

	if (!(S390_lowcore.ext_params & CPU_MF_INT_RI_MASK))
		return;

	if (!current->thread.ri_cb)
		return;
	if (current->thread.ri_signum < SIGRTMIN ||
	    current->thread.ri_signum > SIGRTMAX) {
		WARN_ON_ONCE(1);
		return;
	}

	memset(&info, 0, sizeof(info));
	info.si_signo = current->thread.ri_signum;
	info.si_code = SI_QUEUE;
	if (S390_lowcore.ext_params & CPU_MF_INT_RI_BUF_FULL)
		info.si_int = ENOBUFS;
	else if (S390_lowcore.ext_params & CPU_MF_INT_RI_HALTED)
		info.si_int = ECANCELED;
	else
		/* unknown reason */
		return;

	send_sig_info(current->thread.ri_signum, &info, current);
}