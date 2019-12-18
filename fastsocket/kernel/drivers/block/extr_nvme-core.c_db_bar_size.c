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
struct nvme_dev {int db_stride; } ;

/* Variables and functions */

__attribute__((used)) static size_t db_bar_size(struct nvme_dev *dev, unsigned nr_io_queues)
{
	return 4096 + ((nr_io_queues + 1) << (dev->db_stride + 3));
}