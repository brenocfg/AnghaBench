#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct siginfo {int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_value; int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_errno; int /*<<< orphan*/  si_signo; } ;
struct TYPE_4__ {int sigev_notify; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_value; } ;
struct TYPE_3__ {int mq_curmsgs; } ;
struct mqueue_inode_info {int /*<<< orphan*/  wait_q; int /*<<< orphan*/ * notify_owner; int /*<<< orphan*/  notify_cookie; int /*<<< orphan*/  notify_sock; TYPE_2__ notify; TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFY_WOKENUP ; 
#define  SIGEV_NONE 130 
#define  SIGEV_SIGNAL 129 
#define  SIGEV_THREAD 128 
 int /*<<< orphan*/  SI_MESGQ ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  kill_pid_info (int /*<<< orphan*/ ,struct siginfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlink_sendskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_of_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_tgid_nr_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __do_notify(struct mqueue_inode_info *info)
{
	/* notification
	 * invoked when there is registered process and there isn't process
	 * waiting synchronously for message AND state of queue changed from
	 * empty to not empty. Here we are sure that no one is waiting
	 * synchronously. */
	if (info->notify_owner &&
	    info->attr.mq_curmsgs == 1) {
		struct siginfo sig_i;
		switch (info->notify.sigev_notify) {
		case SIGEV_NONE:
			break;
		case SIGEV_SIGNAL:
			/* sends signal */

			sig_i.si_signo = info->notify.sigev_signo;
			sig_i.si_errno = 0;
			sig_i.si_code = SI_MESGQ;
			sig_i.si_value = info->notify.sigev_value;
			sig_i.si_pid = task_tgid_nr_ns(current,
						ns_of_pid(info->notify_owner));
			sig_i.si_uid = current_uid();

			kill_pid_info(info->notify.sigev_signo,
				      &sig_i, info->notify_owner);
			break;
		case SIGEV_THREAD:
			set_cookie(info->notify_cookie, NOTIFY_WOKENUP);
			netlink_sendskb(info->notify_sock, info->notify_cookie);
			break;
		}
		/* after notification unregisters process */
		put_pid(info->notify_owner);
		info->notify_owner = NULL;
	}
	wake_up(&info->wait_q);
}