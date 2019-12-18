#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct srp_target_port {int /*<<< orphan*/  indirect_size; struct srp_request* req_ring; TYPE_2__* srp_host; } ;
struct srp_request {int /*<<< orphan*/  indirect_desc; scalar_t__ indirect_dma_addr; int /*<<< orphan*/  map_page; int /*<<< orphan*/  fmr_list; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* srp_dev; } ;
struct TYPE_3__ {struct ib_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int SRP_CMD_SQ_SIZE ; 
 int /*<<< orphan*/  ib_dma_unmap_single (struct ib_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srp_free_req_data(struct srp_target_port *target)
{
	struct ib_device *ibdev = target->srp_host->srp_dev->dev;
	struct srp_request *req;
	int i;

	for (i = 0, req = target->req_ring; i < SRP_CMD_SQ_SIZE; ++i, ++req) {
		kfree(req->fmr_list);
		kfree(req->map_page);
		if (req->indirect_dma_addr) {
			ib_dma_unmap_single(ibdev, req->indirect_dma_addr,
					    target->indirect_size,
					    DMA_TO_DEVICE);
		}
		kfree(req->indirect_desc);
	}
}