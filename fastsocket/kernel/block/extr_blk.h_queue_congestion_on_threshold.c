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
struct request_queue {int nr_congestion_on; } ;

/* Variables and functions */

__attribute__((used)) static inline int queue_congestion_on_threshold(struct request_queue *q)
{
	return q->nr_congestion_on;
}