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
struct scsi_device {scalar_t__ lun; scalar_t__ id; scalar_t__ channel; int allow_restart; int inquiry_len; int /*<<< orphan*/  request_queue; TYPE_2__* host; } ;
struct sbp2_lu {int workarounds; struct scsi_device* sdev; TYPE_1__* ud; } ;
struct TYPE_4__ {scalar_t__* hostdata; } ;
struct TYPE_3__ {scalar_t__ id; } ;

/* Variables and functions */
 int ENODEV ; 
 int SBP2_WORKAROUND_INQUIRY_36 ; 
 int /*<<< orphan*/  blk_queue_update_dma_alignment (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sbp2scsi_slave_alloc(struct scsi_device *sdev)
{
	struct sbp2_lu *lu = (struct sbp2_lu *)sdev->host->hostdata[0];

	if (sdev->lun != 0 || sdev->id != lu->ud->id || sdev->channel != 0)
		return -ENODEV;

	lu->sdev = sdev;
	sdev->allow_restart = 1;

	/* SBP-2 requires quadlet alignment of the data buffers. */
	blk_queue_update_dma_alignment(sdev->request_queue, 4 - 1);

	if (lu->workarounds & SBP2_WORKAROUND_INQUIRY_36)
		sdev->inquiry_len = 36;
	return 0;
}