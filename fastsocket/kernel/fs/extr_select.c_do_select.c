#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct poll_wqueues {int error; int /*<<< orphan*/  pt; } ;
struct file_operations {unsigned long (* poll ) (struct file*,int /*<<< orphan*/ *) ;} ;
struct file {struct file_operations* f_op; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {unsigned long* in; unsigned long* out; unsigned long* ex; unsigned long* res_in; unsigned long* res_out; unsigned long* res_ex; } ;
typedef  TYPE_1__ fd_set_bits ;

/* Variables and functions */
 unsigned long DEFAULT_POLLMASK ; 
 unsigned long POLLEX_SET ; 
 unsigned long POLLIN_SET ; 
 unsigned long POLLOUT_SET ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int __NFDBITS ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 struct file* fget_light (int,int*) ; 
 int /*<<< orphan*/  fput_light (struct file*,int) ; 
 int max_select_fd (int,TYPE_1__*) ; 
 int /*<<< orphan*/  poll_freewait (struct poll_wqueues*) ; 
 int /*<<< orphan*/  poll_initwait (struct poll_wqueues*) ; 
 int /*<<< orphan*/  poll_schedule_timeout (struct poll_wqueues*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned long select_estimate_accuracy (struct timespec*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timespec_to_ktime (struct timespec) ; 
 int /*<<< orphan*/  wait_key_set (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long) ; 

int do_select(int n, fd_set_bits *fds, struct timespec *end_time)
{
	ktime_t expire, *to = NULL;
	struct poll_wqueues table;
	poll_table *wait;
	int retval, i, timed_out = 0;
	unsigned long slack = 0;

	rcu_read_lock();
	retval = max_select_fd(n, fds);
	rcu_read_unlock();

	if (retval < 0)
		return retval;
	n = retval;

	poll_initwait(&table);
	wait = &table.pt;
	if (end_time && !end_time->tv_sec && !end_time->tv_nsec) {
		wait = NULL;
		timed_out = 1;
	}

	if (end_time && !timed_out)
		slack = select_estimate_accuracy(end_time);

	retval = 0;
	for (;;) {
		unsigned long *rinp, *routp, *rexp, *inp, *outp, *exp;

		inp = fds->in; outp = fds->out; exp = fds->ex;
		rinp = fds->res_in; routp = fds->res_out; rexp = fds->res_ex;

		for (i = 0; i < n; ++rinp, ++routp, ++rexp) {
			unsigned long in, out, ex, all_bits, bit = 1, mask, j;
			unsigned long res_in = 0, res_out = 0, res_ex = 0;
			const struct file_operations *f_op = NULL;
			struct file *file = NULL;

			in = *inp++; out = *outp++; ex = *exp++;
			all_bits = in | out | ex;
			if (all_bits == 0) {
				i += __NFDBITS;
				continue;
			}

			for (j = 0; j < __NFDBITS; ++j, ++i, bit <<= 1) {
				int fput_needed;
				if (i >= n)
					break;
				if (!(bit & all_bits))
					continue;
				file = fget_light(i, &fput_needed);
				if (file) {
					f_op = file->f_op;
					mask = DEFAULT_POLLMASK;
					if (f_op && f_op->poll) {
						wait_key_set(wait, in, out, bit);
						mask = (*f_op->poll)(file, wait);
					}
					fput_light(file, fput_needed);
					if ((mask & POLLIN_SET) && (in & bit)) {
						res_in |= bit;
						retval++;
						wait = NULL;
					}
					if ((mask & POLLOUT_SET) && (out & bit)) {
						res_out |= bit;
						retval++;
						wait = NULL;
					}
					if ((mask & POLLEX_SET) && (ex & bit)) {
						res_ex |= bit;
						retval++;
						wait = NULL;
					}
				}
			}
			if (res_in)
				*rinp = res_in;
			if (res_out)
				*routp = res_out;
			if (res_ex)
				*rexp = res_ex;
			cond_resched();
		}
		wait = NULL;
		if (retval || timed_out || signal_pending(current))
			break;
		if (table.error) {
			retval = table.error;
			break;
		}

		/*
		 * If this is the first loop and we have a timeout
		 * given, then we convert to ktime_t and set the to
		 * pointer to the expiry value.
		 */
		if (end_time && !to) {
			expire = timespec_to_ktime(*end_time);
			to = &expire;
		}

		if (!poll_schedule_timeout(&table, TASK_INTERRUPTIBLE,
					   to, slack))
			timed_out = 1;
	}

	poll_freewait(&table);

	return retval;
}