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
struct pktgen_thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  if_lock (struct pktgen_thread*) ; 
 int /*<<< orphan*/  if_unlock (struct pktgen_thread*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_is_running (struct pktgen_thread*) ; 

__attribute__((used)) static int pktgen_wait_thread_run(struct pktgen_thread *t)
{
	if_lock(t);

	while (thread_is_running(t)) {

		if_unlock(t);

		msleep_interruptible(100);

		if (signal_pending(current))
			goto signal;
		if_lock(t);
	}
	if_unlock(t);
	return 1;
signal:
	return 0;
}