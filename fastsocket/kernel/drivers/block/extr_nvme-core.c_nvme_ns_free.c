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
struct nvme_ns {int /*<<< orphan*/  queue; TYPE_1__* disk; } ;
struct TYPE_2__ {int first_minor; } ;

/* Variables and functions */
 int NVME_MINORS ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_put_ns_idx (int) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 

__attribute__((used)) static void nvme_ns_free(struct nvme_ns *ns)
{
	int index = ns->disk->first_minor / NVME_MINORS;
	put_disk(ns->disk);
	nvme_put_ns_idx(index);
	blk_cleanup_queue(ns->queue);
	kfree(ns);
}