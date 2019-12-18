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
typedef  int /*<<< orphan*/  thread_continue_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_WORKER_SX_INIT () ; 
 scalar_t__ THREAD_NULL ; 
 scalar_t__ audit_thread ; 
 scalar_t__ audit_worker ; 
 int /*<<< orphan*/  kernel_thread_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
audit_worker_init(void)
{

	AUDIT_WORKER_SX_INIT();
	kernel_thread_start((thread_continue_t)audit_worker, NULL,
	    &audit_thread);
	if (audit_thread == THREAD_NULL)
		panic("audit_worker_init: Couldn't create audit_worker thread");
}