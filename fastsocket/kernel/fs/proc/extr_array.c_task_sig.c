#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  signal; } ;
struct task_struct {TYPE_5__* signal; int /*<<< orphan*/  blocked; TYPE_1__ pending; } ;
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_12__ {TYPE_3__* user; } ;
struct TYPE_8__ {int /*<<< orphan*/  signal; } ;
struct TYPE_11__ {TYPE_4__* rlim; int /*<<< orphan*/  count; TYPE_2__ shared_pending; } ;
struct TYPE_10__ {unsigned long rlim_cur; } ;
struct TYPE_9__ {int /*<<< orphan*/  sigpending; } ;

/* Variables and functions */
 size_t RLIMIT_SIGPENDING ; 
 TYPE_6__* __task_cred (struct task_struct*) ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  collect_sigign_sigcatch (struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  render_sigset_t (struct seq_file*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static inline void task_sig(struct seq_file *m, struct task_struct *p)
{
	unsigned long flags;
	sigset_t pending, shpending, blocked, ignored, caught;
	int num_threads = 0;
	unsigned long qsize = 0;
	unsigned long qlim = 0;

	sigemptyset(&pending);
	sigemptyset(&shpending);
	sigemptyset(&blocked);
	sigemptyset(&ignored);
	sigemptyset(&caught);

	if (lock_task_sighand(p, &flags)) {
		pending = p->pending.signal;
		shpending = p->signal->shared_pending.signal;
		blocked = p->blocked;
		collect_sigign_sigcatch(p, &ignored, &caught);
		num_threads = atomic_read(&p->signal->count);
		qsize = atomic_read(&__task_cred(p)->user->sigpending);
		qlim = p->signal->rlim[RLIMIT_SIGPENDING].rlim_cur;
		unlock_task_sighand(p, &flags);
	}

	seq_printf(m, "Threads:\t%d\n", num_threads);
	seq_printf(m, "SigQ:\t%lu/%lu\n", qsize, qlim);

	/* render them all */
	render_sigset_t(m, "SigPnd:\t", &pending);
	render_sigset_t(m, "ShdPnd:\t", &shpending);
	render_sigset_t(m, "SigBlk:\t", &blocked);
	render_sigset_t(m, "SigIgn:\t", &ignored);
	render_sigset_t(m, "SigCgt:\t", &caught);
}