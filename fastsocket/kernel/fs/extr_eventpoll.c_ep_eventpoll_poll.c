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
struct readyevents_arg {struct eventpoll* ep; int /*<<< orphan*/  locked; } ;
struct file {struct eventpoll* private_data; } ;
struct eventpoll {int /*<<< orphan*/  poll_wait; } ;
struct TYPE_4__ {scalar_t__ qproc; } ;
typedef  TYPE_1__ poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  EP_MAX_NESTS ; 
 int /*<<< orphan*/  current ; 
 int ep_call_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct readyevents_arg*,struct eventpoll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep_poll_readyevents_proc ; 
 scalar_t__ ep_ptable_queue_proc ; 
 int /*<<< orphan*/  poll_readywalk_ncalls ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static unsigned int ep_eventpoll_poll(struct file *file, poll_table *wait)
{
	int pollflags;
	struct eventpoll *ep = file->private_data;
	struct readyevents_arg arg;

	/*
	 * During ep_insert() we already hold the ep->mtx for the tfile.
	 * Prevent re-aquisition.
	 */
	arg.locked = wait && (wait->qproc == ep_ptable_queue_proc);
	arg.ep = ep;

	/* Insert inside our poll wait queue */
	poll_wait(file, &ep->poll_wait, wait);

	/*
	 * Proceed to find out if wanted events are really available inside
	 * the ready list. This need to be done under ep_call_nested()
	 * supervision, since the call to f_op->poll() done on listed files
	 * could re-enter here.
	 */
	pollflags = ep_call_nested(&poll_readywalk_ncalls, EP_MAX_NESTS,
				   ep_poll_readyevents_proc, &arg, ep, current);

	return pollflags != -1 ? pollflags : 0;
}