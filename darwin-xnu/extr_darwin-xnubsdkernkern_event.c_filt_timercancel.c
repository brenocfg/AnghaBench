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
typedef  int /*<<< orphan*/  thread_call_t ;
struct knote {scalar_t__ kn_hook; int /*<<< orphan*/  kn_hookid; } ;

/* Variables and functions */
 scalar_t__ TIMER_ARMED ; 
 int /*<<< orphan*/  TIMER_IDLE ; 
 scalar_t__ os_atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relaxed ; 
 int /*<<< orphan*/  thread_call_cancel_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filt_timercancel(struct knote *kn)
{
	if (os_atomic_xchg(&kn->kn_hookid, TIMER_IDLE, relaxed) == TIMER_ARMED) {
		/* cancel the thread call and wait for any filt_timerexpire in flight */
		thread_call_cancel_wait((thread_call_t)kn->kn_hook);
	}
}