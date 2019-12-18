#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ VCOS_MSG_T ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * tail; TYPE_1__* head; int /*<<< orphan*/  sem; } ;
typedef  TYPE_2__ VCOS_MSGQUEUE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 

VCOS_MSG_T *vcos_msg_wait(VCOS_MSGQUEUE_T *queue)
{
   VCOS_MSG_T *msg;
   vcos_semaphore_wait(&queue->sem);
   vcos_mutex_lock(&queue->lock);

   msg = queue->head;
   vcos_assert(msg);    /* should always be a message here! */

   queue->head = msg->next;
   if (queue->head == NULL)
      queue->tail = NULL;

   vcos_mutex_unlock(&queue->lock);
   return msg;
}