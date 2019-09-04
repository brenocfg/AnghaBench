#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int boolean_t ;
struct TYPE_3__ {int state; scalar_t__ block_hint; } ;

/* Variables and functions */
 int TH_WAIT ; 
 scalar_t__ kThreadWaitParkedWorkQueue ; 

boolean_t
stackshot_thread_is_idle_worker_unsafe(thread_t thread)
{
	/* When the pthread kext puts a worker thread to sleep, it will
	 * set kThreadWaitParkedWorkQueue in the block_hint of the thread
	 * struct. See parkit() in kern/kern_support.c in libpthread.
	 */
	return (thread->state & TH_WAIT) &&
		(thread->block_hint == kThreadWaitParkedWorkQueue);
}