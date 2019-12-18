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
typedef  scalar_t__ dispatch_semaphore_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_TIME_FOREVER ; 
 int RECURSE_START_OFFSET ; 
 int /*<<< orphan*/  T_LOG (char*,unsigned int,int) ; 
 int USER_FRAMES ; 
 int /*<<< orphan*/  backtrace_go ; 
 int /*<<< orphan*/  backtrace_started ; 
 int /*<<< orphan*/  dispatch_semaphore_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispatch_semaphore_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recurse_a (scalar_t__,unsigned int) ; 

__attribute__((used)) static void *
backtrace_thread(void *arg)
{
    dispatch_semaphore_t notify_spinning;
    unsigned int calls;

    notify_spinning = (dispatch_semaphore_t)arg;

    dispatch_semaphore_signal(backtrace_started);
    if (!notify_spinning) {
        dispatch_semaphore_wait(backtrace_go, DISPATCH_TIME_FOREVER);
    }

    /*
     * backtrace_thread, recurse_a, recurse_b, ...[, __kdebug_trace64]
     *
     * Always make one less call for this frame (backtrace_thread).
     */
    calls = USER_FRAMES - RECURSE_START_OFFSET - 1 /* backtrace_thread */;
    if (notify_spinning) {
        /*
         * Spinning doesn't end up calling __kdebug_trace64.
         */
        calls -= 1;
    }

    T_LOG("backtrace thread calling into %d frames (already at %d frames)",
        calls, RECURSE_START_OFFSET);
    (void)recurse_a(notify_spinning, calls);
    return NULL;
}