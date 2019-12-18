#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct scsi_cmnd {int sc_data_direction; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; } ;
struct sbp2_lu {TYPE_3__* hi; int /*<<< orphan*/  speed_code; int /*<<< orphan*/  max_payload_size; } ;
struct sbp2_command_orb {int next_ORB_lo; int data_descriptor_hi; int data_descriptor_lo; int /*<<< orphan*/  cdb; int /*<<< orphan*/  misc; int /*<<< orphan*/  next_ORB_hi; } ;
struct sbp2_command_info {int /*<<< orphan*/  command_orb_dma; struct sbp2_command_orb command_orb; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {TYPE_2__* host; } ;
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_5__ {TYPE_1__ device; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 scalar_t__ ORB_DIRECTION_NO_DATA_TRANSFER ; 
 scalar_t__ ORB_DIRECTION_READ_FROM_MEDIA ; 
 scalar_t__ ORB_DIRECTION_WRITE_TO_MEDIA ; 
 int /*<<< orphan*/  ORB_SET_DIRECTION (int) ; 
 int /*<<< orphan*/  ORB_SET_MAX_PAYLOAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ORB_SET_NOTIFY (int) ; 
 int /*<<< orphan*/  ORB_SET_NULL_PTR (int) ; 
 int /*<<< orphan*/  ORB_SET_SPEED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBP2_INFO (char*) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (struct device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sbp2_prep_command_orb_sg (struct sbp2_command_orb*,TYPE_3__*,struct sbp2_command_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sbp2util_cpu_to_be32_buffer (struct sbp2_command_orb*,int) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 

__attribute__((used)) static int sbp2_create_command_orb(struct sbp2_lu *lu,
				   struct sbp2_command_info *cmd,
				   struct scsi_cmnd *SCpnt)
{
	struct device *dmadev = lu->hi->host->device.parent;
	struct sbp2_command_orb *orb = &cmd->command_orb;
	unsigned int scsi_request_bufflen = scsi_bufflen(SCpnt);
	enum dma_data_direction dma_dir = SCpnt->sc_data_direction;
	u32 orb_direction;
	int ret;

	dma_sync_single_for_cpu(dmadev, cmd->command_orb_dma,
				sizeof(struct sbp2_command_orb), DMA_TO_DEVICE);
	/*
	 * Set-up our command ORB.
	 *
	 * NOTE: We're doing unrestricted page tables (s/g), as this is
	 * best performance (at least with the devices I have). This means
	 * that data_size becomes the number of s/g elements, and
	 * page_size should be zero (for unrestricted).
	 */
	orb->next_ORB_hi = ORB_SET_NULL_PTR(1);
	orb->next_ORB_lo = 0x0;
	orb->misc = ORB_SET_MAX_PAYLOAD(lu->max_payload_size);
	orb->misc |= ORB_SET_SPEED(lu->speed_code);
	orb->misc |= ORB_SET_NOTIFY(1);

	if (dma_dir == DMA_NONE)
		orb_direction = ORB_DIRECTION_NO_DATA_TRANSFER;
	else if (dma_dir == DMA_TO_DEVICE && scsi_request_bufflen)
		orb_direction = ORB_DIRECTION_WRITE_TO_MEDIA;
	else if (dma_dir == DMA_FROM_DEVICE && scsi_request_bufflen)
		orb_direction = ORB_DIRECTION_READ_FROM_MEDIA;
	else {
		SBP2_INFO("Falling back to DMA_NONE");
		orb_direction = ORB_DIRECTION_NO_DATA_TRANSFER;
	}

	/* set up our page table stuff */
	if (orb_direction == ORB_DIRECTION_NO_DATA_TRANSFER) {
		orb->data_descriptor_hi = 0x0;
		orb->data_descriptor_lo = 0x0;
		orb->misc |= ORB_SET_DIRECTION(1);
		ret = 0;
	} else {
		ret = sbp2_prep_command_orb_sg(orb, lu->hi, cmd,
					       scsi_sg_count(SCpnt),
					       scsi_sglist(SCpnt),
					       orb_direction, dma_dir);
	}
	sbp2util_cpu_to_be32_buffer(orb, sizeof(*orb));

	memset(orb->cdb, 0, sizeof(orb->cdb));
	memcpy(orb->cdb, SCpnt->cmnd, SCpnt->cmd_len);

	dma_sync_single_for_device(dmadev, cmd->command_orb_dma,
			sizeof(struct sbp2_command_orb), DMA_TO_DEVICE);
	return ret;
}