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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_3__ {int /*<<< orphan*/  imq_wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAITQ_KEEP_LOCKED ; 
 int /*<<< orphan*/  waitq_prepost_reserve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
imq_reserve_and_lock(ipc_mqueue_t mq, uint64_t *reserved_prepost)
{
	*reserved_prepost = waitq_prepost_reserve(&mq->imq_wait_queue, 0,
						  WAITQ_KEEP_LOCKED);

}