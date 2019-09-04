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

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_NOTNULL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  backtrace_go ; 
 int /*<<< orphan*/  dispatch_semaphore_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_backtrace_thread(void)
{
    T_QUIET; T_ASSERT_NOTNULL(backtrace_go,
        "thread to backtrace created before starting it");
    dispatch_semaphore_signal(backtrace_go);
}