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
typedef  int __u32 ;
struct TYPE_2__ {scalar_t__ replacement_session_keyring; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_IRET ; 
 int /*<<< orphan*/  TIF_NOTIFY_RESUME ; 
 int _TIF_MCE_NOTIFY ; 
 int _TIF_NOTIFY_RESUME ; 
 int _TIF_SIGPENDING ; 
 int _TIF_USER_RETURN_NOTIFY ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  do_signal (struct pt_regs*) ; 
 int /*<<< orphan*/  fire_user_return_notifiers () ; 
 int /*<<< orphan*/  key_replace_session_keyring () ; 
 int /*<<< orphan*/  mce_notify_process () ; 
 int /*<<< orphan*/  tracehook_notify_resume (struct pt_regs*) ; 

void
do_notify_resume(struct pt_regs *regs, void *unused, __u32 thread_info_flags)
{
#ifdef CONFIG_X86_MCE
	/* notify userspace of pending MCEs */
	if (thread_info_flags & _TIF_MCE_NOTIFY)
		mce_notify_process();
#endif /* CONFIG_X86_64 && CONFIG_X86_MCE */

	/* deal with pending signal delivery */
	if (thread_info_flags & _TIF_SIGPENDING)
		do_signal(regs);

	if (thread_info_flags & _TIF_NOTIFY_RESUME) {
		clear_thread_flag(TIF_NOTIFY_RESUME);
		tracehook_notify_resume(regs);
		if (current->replacement_session_keyring)
			key_replace_session_keyring();
	}
	if (thread_info_flags & _TIF_USER_RETURN_NOTIFY)
		fire_user_return_notifiers();

#ifdef CONFIG_X86_32
	clear_thread_flag(TIF_IRET);
#endif /* CONFIG_X86_32 */
}