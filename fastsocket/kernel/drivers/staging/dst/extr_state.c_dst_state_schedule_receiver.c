#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dst_state {TYPE_1__* node; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  dst_recv ; 
 int /*<<< orphan*/  dst_thread_setup ; 
 int thread_pool_schedule_private (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dst_state*,int /*<<< orphan*/ ,TYPE_1__*) ; 

int dst_state_schedule_receiver(struct dst_state *st)
{
	return thread_pool_schedule_private(st->node->pool, dst_thread_setup,
			dst_recv, st, MAX_SCHEDULE_TIMEOUT, st->node);
}