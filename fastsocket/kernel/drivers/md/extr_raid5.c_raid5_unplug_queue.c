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
struct request_queue {struct mddev* queuedata; } ;
struct mddev {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  md_raid5_unplug_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raid5_unplug_queue(struct request_queue *q)
{
	struct mddev *mddev = q->queuedata;
	md_raid5_unplug_device(mddev->private);
}