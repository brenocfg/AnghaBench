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
struct data_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2x00queue_empty (struct data_queue*) ; 

void rt2x00mmio_flush_queue(struct data_queue *queue, bool drop)
{
	unsigned int i;

	for (i = 0; !rt2x00queue_empty(queue) && i < 10; i++)
		msleep(10);
}