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
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_QUEUED ; 
 int /*<<< orphan*/  queue_flag_clear_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 

void blk_queue_free_tags(struct request_queue *q)
{
	queue_flag_clear_unlocked(QUEUE_FLAG_QUEUED, q);
}