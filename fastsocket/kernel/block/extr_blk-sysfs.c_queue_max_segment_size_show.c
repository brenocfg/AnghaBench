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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  QUEUE_FLAG_CLUSTER ; 
 int /*<<< orphan*/  queue_max_segment_size (struct request_queue*) ; 
 int /*<<< orphan*/  queue_var_show (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t queue_max_segment_size_show(struct request_queue *q, char *page)
{
	if (test_bit(QUEUE_FLAG_CLUSTER, &q->queue_flags))
		return queue_var_show(queue_max_segment_size(q), (page));

	return queue_var_show(PAGE_CACHE_SIZE, (page));
}