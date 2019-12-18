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
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {int state; int block_hint; } ;

/* Variables and functions */
 int TH_WAIT ; 
#define  kThreadWaitNone 133 
#define  kThreadWaitPThreadCondVar 132 
#define  kThreadWaitPThreadMutex 131 
#define  kThreadWaitPThreadRWLockRead 130 
#define  kThreadWaitPThreadRWLockWrite 129 
#define  kThreadWaitParkedWorkQueue 128 
 int /*<<< orphan*/ * kdp_pthread_get_thread_kwq (TYPE_1__*) ; 

__attribute__((used)) static int
stackshot_thread_has_valid_waitinfo(thread_t thread)
{
	if (!(thread->state & TH_WAIT))
		return 0;

	switch (thread->block_hint) {
		// If set to None or is a parked work queue, ignore it
		case kThreadWaitParkedWorkQueue:
		case kThreadWaitNone:
			return 0;
		// There is a short window where the pthread kext removes a thread
		// from its ksyn wait queue before waking the thread up
		case kThreadWaitPThreadMutex:
		case kThreadWaitPThreadRWLockRead:
		case kThreadWaitPThreadRWLockWrite:
		case kThreadWaitPThreadCondVar:
			return (kdp_pthread_get_thread_kwq(thread) != NULL);
		// All other cases are valid block hints if in a wait state
		default:
			return 1;
	}
}