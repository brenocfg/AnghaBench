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
typedef  int /*<<< orphan*/  VCOS_MSG_WAITER_T ;
typedef  int /*<<< orphan*/  VCOS_MSG_T ;
struct TYPE_3__ {int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ VCOS_MSGQUEUE_T ;

/* Variables and functions */
 int /*<<< orphan*/  msgq_append (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vcos_msgq_queue_waiter_on_reply(VCOS_MSG_WAITER_T *waiter,
                                            VCOS_MSG_T *msg)
{
   VCOS_MSGQUEUE_T *queue = (VCOS_MSGQUEUE_T*)waiter;
   msgq_append(queue, msg);
   vcos_semaphore_post(&queue->sem);
}