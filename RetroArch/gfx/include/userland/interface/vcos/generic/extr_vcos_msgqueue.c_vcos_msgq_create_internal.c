#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_5__ {int /*<<< orphan*/  on_reply; } ;
struct TYPE_6__ {int /*<<< orphan*/  sem; int /*<<< orphan*/  lock; TYPE_1__ waiter; } ;
typedef  TYPE_2__ VCOS_MSGQUEUE_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcos_msgq_queue_waiter_on_reply ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VCOS_STATUS_T vcos_msgq_create_internal(VCOS_MSGQUEUE_T *q, const char *name)
{
   VCOS_STATUS_T st;

   memset(q, 0, sizeof(*q));

   q->waiter.on_reply = vcos_msgq_queue_waiter_on_reply;
   st = vcos_semaphore_create(&q->sem, name, 0);
   if (st != VCOS_SUCCESS)
      goto fail_sem;

   st = vcos_mutex_create(&q->lock, name);
   if (st != VCOS_SUCCESS)
      goto fail_mtx;

   return st;

fail_mtx:
   vcos_semaphore_delete(&q->sem);
fail_sem:
   return st;
}