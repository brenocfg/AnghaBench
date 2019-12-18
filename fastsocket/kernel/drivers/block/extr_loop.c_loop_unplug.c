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
struct request_queue {struct loop_device* queuedata; } ;
struct loop_device {TYPE_1__* lo_backing_file; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_PLUGGED ; 
 int /*<<< orphan*/  blk_run_address_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_flag_clear_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 

__attribute__((used)) static void loop_unplug(struct request_queue *q)
{
	struct loop_device *lo = q->queuedata;

	queue_flag_clear_unlocked(QUEUE_FLAG_PLUGGED, q);
	blk_run_address_space(lo->lo_backing_file->f_mapping);
}