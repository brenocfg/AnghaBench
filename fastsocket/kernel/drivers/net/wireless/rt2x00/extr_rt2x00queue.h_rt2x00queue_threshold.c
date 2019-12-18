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
struct data_queue {scalar_t__ threshold; } ;

/* Variables and functions */
 scalar_t__ rt2x00queue_available (struct data_queue*) ; 

__attribute__((used)) static inline int rt2x00queue_threshold(struct data_queue *queue)
{
	return rt2x00queue_available(queue) < queue->threshold;
}