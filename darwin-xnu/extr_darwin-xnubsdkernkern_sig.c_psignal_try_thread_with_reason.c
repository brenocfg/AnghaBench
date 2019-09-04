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
typedef  int /*<<< orphan*/  thread_t ;
struct os_reason {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSIG_TRY_THREAD ; 
 int /*<<< orphan*/  TASK_NULL ; 
 int /*<<< orphan*/  psignal_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct os_reason*) ; 

void
psignal_try_thread_with_reason(proc_t p, thread_t thread, int signum, struct os_reason *signal_reason)
{
	psignal_internal(p, TASK_NULL, thread, PSIG_TRY_THREAD, signum, signal_reason);
}