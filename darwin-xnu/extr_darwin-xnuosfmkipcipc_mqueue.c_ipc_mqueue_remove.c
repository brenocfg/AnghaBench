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
struct waitq_set {int dummy; } ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_4__ {struct waitq_set imq_set_queue; struct waitq imq_wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  waitq_unlink (struct waitq*,struct waitq_set*) ; 

kern_return_t
ipc_mqueue_remove(
	ipc_mqueue_t	  mqueue,
	ipc_mqueue_t	  set_mqueue)
{
	struct waitq *mq_waitq = &mqueue->imq_wait_queue;
	struct waitq_set *set_waitq = &set_mqueue->imq_set_queue;

	return waitq_unlink(mq_waitq, set_waitq);
}