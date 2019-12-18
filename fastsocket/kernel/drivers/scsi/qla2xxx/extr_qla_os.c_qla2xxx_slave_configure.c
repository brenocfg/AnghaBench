#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {scalar_t__ tagged_supported; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  host; } ;
struct req_que {int /*<<< orphan*/  max_q_depth; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw; struct req_que* req; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 scalar_t__ IS_T10_PI_CAPABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_update_dma_alignment (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_activate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_deactivate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla2xxx_slave_configure(struct scsi_device *sdev)
{
	scsi_qla_host_t *vha = shost_priv(sdev->host);
	struct req_que *req = vha->req;

	if (IS_T10_PI_CAPABLE(vha->hw))
		blk_queue_update_dma_alignment(sdev->request_queue, 0x7);

	if (sdev->tagged_supported)
		scsi_activate_tcq(sdev, req->max_q_depth);
	else
		scsi_deactivate_tcq(sdev, req->max_q_depth);
	return 0;
}