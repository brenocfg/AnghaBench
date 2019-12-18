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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_4__ {int /*<<< orphan*/  imq_wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imq_held (TYPE_1__*) ; 
 int /*<<< orphan*/  waitq_prepost_release_reserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_unlock (int /*<<< orphan*/ *) ; 

void
imq_release_and_unlock(ipc_mqueue_t mq, uint64_t reserved_prepost)
{
	assert(imq_held(mq));
	waitq_unlock(&mq->imq_wait_queue);
	waitq_prepost_release_reserve(reserved_prepost);
}