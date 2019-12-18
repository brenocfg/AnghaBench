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
struct scsi_device {int allow_restart; int inquiry_len; int /*<<< orphan*/  request_queue; struct sbp2_logical_unit* hostdata; } ;
struct sbp2_logical_unit {TYPE_1__* tgt; } ;
struct TYPE_2__ {int workarounds; } ;

/* Variables and functions */
 int ENOSYS ; 
 int SBP2_WORKAROUND_INQUIRY_36 ; 
 int /*<<< orphan*/  blk_queue_update_dma_alignment (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sbp2_scsi_slave_alloc(struct scsi_device *sdev)
{
	struct sbp2_logical_unit *lu = sdev->hostdata;

	/* (Re-)Adding logical units via the SCSI stack is not supported. */
	if (!lu)
		return -ENOSYS;

	sdev->allow_restart = 1;

	/* SBP-2 requires quadlet alignment of the data buffers. */
	blk_queue_update_dma_alignment(sdev->request_queue, 4 - 1);

	if (lu->tgt->workarounds & SBP2_WORKAROUND_INQUIRY_36)
		sdev->inquiry_len = 36;

	return 0;
}