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
struct bpf_d {int /*<<< orphan*/  bd_thread_call; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  thread_call_cancel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
bpf_stop_timer(struct bpf_d *d)
{
	/*
	 * If the timer has already gone off, this does nothing.
	 * Our caller is expected to set d->bd_state to BPF_IDLE,
	 * with the bpf_mlock, after we are called. bpf_timed_out()
	 * also grabs bpf_mlock, so, if the timer has gone off and
	 * bpf_timed_out() hasn't finished, it's waiting for the
	 * lock; when this thread releases the lock, it will
	 * find the state is BPF_IDLE, and just release the
	 * lock and return.
	 */
	return (thread_call_cancel(d->bd_thread_call));
}