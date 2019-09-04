#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mpqueue_head_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_call_lck_attr ; 
 int /*<<< orphan*/  timer_call_lck_grp ; 

void
timer_call_queue_init(mpqueue_head_t *queue)
{
	DBG("timer_call_queue_init(%p)\n", queue);
	mpqueue_init(queue, &timer_call_lck_grp, &timer_call_lck_attr);
}