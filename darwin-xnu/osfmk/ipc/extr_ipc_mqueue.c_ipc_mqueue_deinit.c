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
typedef  TYPE_1__* ipc_mqueue_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  imq_wait_queue; int /*<<< orphan*/  imq_set_queue; } ;

/* Variables and functions */
 scalar_t__ imq_is_set (TYPE_1__*) ; 
 int /*<<< orphan*/  waitq_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_set_deinit (int /*<<< orphan*/ *) ; 

void ipc_mqueue_deinit(
	ipc_mqueue_t		mqueue)
{
	boolean_t is_set = imq_is_set(mqueue);

	if (is_set)
		waitq_set_deinit(&mqueue->imq_set_queue);
	else
		waitq_deinit(&mqueue->imq_wait_queue);
}