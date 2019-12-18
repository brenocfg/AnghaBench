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
struct srp_target_port {TYPE_2__* srp_host; } ;
struct srp_request {int /*<<< orphan*/  nfmr; struct ib_pool_fmr** fmr_list; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct ib_pool_fmr {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* srp_dev; } ;
struct TYPE_3__ {struct ib_device* dev; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ib_fmr_pool_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 

__attribute__((used)) static void srp_unmap_data(struct scsi_cmnd *scmnd,
			   struct srp_target_port *target,
			   struct srp_request *req)
{
	struct ib_device *ibdev = target->srp_host->srp_dev->dev;
	struct ib_pool_fmr **pfmr;

	if (!scsi_sglist(scmnd) ||
	    (scmnd->sc_data_direction != DMA_TO_DEVICE &&
	     scmnd->sc_data_direction != DMA_FROM_DEVICE))
		return;

	pfmr = req->fmr_list;
	while (req->nfmr--)
		ib_fmr_pool_unmap(*pfmr++);

	ib_dma_unmap_sg(ibdev, scsi_sglist(scmnd), scsi_sg_count(scmnd),
			scmnd->sc_data_direction);
}