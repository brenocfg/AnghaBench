#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int wait_type; int /*<<< orphan*/  context; int /*<<< orphan*/  owner; int /*<<< orphan*/  waiter; } ;
typedef  TYPE_1__ thread_waitinfo_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_19__ {int block_hint; int /*<<< orphan*/  wait_event; int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
#define  kThreadWaitKernelMutex 141 
#define  kThreadWaitKernelRWLockRead 140 
#define  kThreadWaitKernelRWLockUpgrade 139 
#define  kThreadWaitKernelRWLockWrite 138 
#define  kThreadWaitOnProcess 137 
#define  kThreadWaitPThreadCondVar 136 
#define  kThreadWaitPThreadMutex 135 
#define  kThreadWaitPThreadRWLockRead 134 
#define  kThreadWaitPThreadRWLockWrite 133 
#define  kThreadWaitPortReceive 132 
#define  kThreadWaitPortSend 131 
#define  kThreadWaitSemaphore 130 
#define  kThreadWaitUserLock 129 
#define  kThreadWaitWorkloopSyncWait 128 
 int /*<<< orphan*/  kdp_lck_mtx_find_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kdp_mqueue_recv_find_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kdp_mqueue_send_find_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kdp_pthread_find_owner (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  kdp_rwlck_find_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kdp_sema_find_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kdp_ulock_find_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kdp_wait4_find_process (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kdp_workloop_sync_wait_find_owner (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  thread_tid (TYPE_2__*) ; 

__attribute__((used)) static void
stackshot_thread_wait_owner_info(thread_t thread, thread_waitinfo_t *waitinfo)
{
	waitinfo->waiter    = thread_tid(thread);
	waitinfo->wait_type = thread->block_hint;
	switch (waitinfo->wait_type) {
		case kThreadWaitKernelMutex:
			kdp_lck_mtx_find_owner(thread->waitq, thread->wait_event, waitinfo);
			break;
		case kThreadWaitPortReceive:
			kdp_mqueue_recv_find_owner(thread->waitq, thread->wait_event, waitinfo);
			break;
		case kThreadWaitPortSend:
			kdp_mqueue_send_find_owner(thread->waitq, thread->wait_event, waitinfo);
			break;
		case kThreadWaitSemaphore:
			kdp_sema_find_owner(thread->waitq, thread->wait_event, waitinfo);
			break;
		case kThreadWaitUserLock:
			kdp_ulock_find_owner(thread->waitq, thread->wait_event, waitinfo);
			break;
		case kThreadWaitKernelRWLockRead:
		case kThreadWaitKernelRWLockWrite:
		case kThreadWaitKernelRWLockUpgrade:
			kdp_rwlck_find_owner(thread->waitq, thread->wait_event, waitinfo);
			break;
		case kThreadWaitPThreadMutex:
		case kThreadWaitPThreadRWLockRead:
		case kThreadWaitPThreadRWLockWrite:
		case kThreadWaitPThreadCondVar:
			kdp_pthread_find_owner(thread, waitinfo);
			break;
		case kThreadWaitWorkloopSyncWait:
			kdp_workloop_sync_wait_find_owner(thread, thread->wait_event, waitinfo);
			break;
		case kThreadWaitOnProcess:
			kdp_wait4_find_process(thread, thread->wait_event, waitinfo);
			break;
		default:
			waitinfo->owner = 0;
			waitinfo->context = 0;
			break;
	}
}