#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_7__ {scalar_t__ magic; int /*<<< orphan*/ * waiter; } ;
typedef  TYPE_1__ VCOS_MSG_T ;
struct TYPE_8__ {int /*<<< orphan*/  waitsem; int /*<<< orphan*/  waiter; } ;
typedef  TYPE_2__ VCOS_MSG_SIMPLE_WAITER_T ;
typedef  int /*<<< orphan*/  VCOS_MSGQUEUE_T ;

/* Variables and functions */
 scalar_t__ MAGIC ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_msg_send_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_msgq_simple_waiter_deinit (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_msgq_simple_waiter_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 

VCOS_STATUS_T vcos_msg_sendwait(VCOS_MSGQUEUE_T *dest, uint32_t code, VCOS_MSG_T *msg)
{
   VCOS_STATUS_T st;
   VCOS_MSG_SIMPLE_WAITER_T waiter;

   vcos_assert(msg->magic == MAGIC);

   /* if this fires, you've set a waiter up but are now about to obliterate it
    * with the 'wait for a reply' waiter.
    */
   vcos_assert(msg->waiter == NULL);

   if ((st=vcos_msgq_simple_waiter_init(&waiter)) != VCOS_SUCCESS)
      return st;

   vcos_msg_send_helper(&waiter.waiter, dest, code, msg);
   vcos_semaphore_wait(&waiter.waitsem);
   vcos_msgq_simple_waiter_deinit(&waiter);

   return VCOS_SUCCESS;
}