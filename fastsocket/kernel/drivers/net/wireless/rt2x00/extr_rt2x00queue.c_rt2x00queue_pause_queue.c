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
struct data_queue {int /*<<< orphan*/  flags; TYPE_1__* rt2x00dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 int /*<<< orphan*/  QUEUE_PAUSED ; 
 int /*<<< orphan*/  QUEUE_STARTED ; 
 int /*<<< orphan*/  rt2x00queue_pause_queue_nocheck (struct data_queue*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00queue_pause_queue(struct data_queue *queue)
{
	if (!test_bit(DEVICE_STATE_PRESENT, &queue->rt2x00dev->flags) ||
	    !test_bit(QUEUE_STARTED, &queue->flags) ||
	    test_and_set_bit(QUEUE_PAUSED, &queue->flags))
		return;

	rt2x00queue_pause_queue_nocheck(queue);
}