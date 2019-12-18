#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_4__ {int /*<<< orphan*/  on_reply; } ;
struct TYPE_5__ {TYPE_1__ waiter; int /*<<< orphan*/  waitsem; } ;
typedef  TYPE_2__ VCOS_MSG_SIMPLE_WAITER_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_msgq_simple_waiter_on_reply ; 
 int /*<<< orphan*/  vcos_semaphore_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VCOS_STATUS_T vcos_msgq_simple_waiter_init(VCOS_MSG_SIMPLE_WAITER_T *waiter)
{
   VCOS_STATUS_T status;
   status = vcos_semaphore_create(&waiter->waitsem, "waiter", 0);
   waiter->waiter.on_reply = vcos_msgq_simple_waiter_on_reply;
   return status;
}