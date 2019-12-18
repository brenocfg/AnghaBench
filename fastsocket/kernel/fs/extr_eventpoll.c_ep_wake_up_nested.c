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
typedef  int /*<<< orphan*/  wait_queue_head_t ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_poll (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void ep_wake_up_nested(wait_queue_head_t *wqueue,
				     unsigned long events, int subclass)
{
	wake_up_poll(wqueue, events);
}