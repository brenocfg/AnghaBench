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
struct nvme_dev {int queue_count; int /*<<< orphan*/ ** queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_free_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_free_queues(struct nvme_dev *dev)
{
	int i;

	for (i = dev->queue_count - 1; i >= 0; i--) {
		nvme_free_queue(dev->queues[i]);
		dev->queue_count--;
		dev->queues[i] = NULL;
	}
}