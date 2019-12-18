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
struct TYPE_2__ {scalar_t__* cdb; int scsi_status; int srb_status; int /*<<< orphan*/  data_transfer_length; int /*<<< orphan*/  sense_info_length; int /*<<< orphan*/  sense_data; } ;
struct vstor_packet {TYPE_1__ vm_srb; } ;
struct storvsc_device {int /*<<< orphan*/  waiting_to_drain; scalar_t__ drain_notify; int /*<<< orphan*/  num_outstanding_req; } ;
struct storvsc_cmd_request {int /*<<< orphan*/  sense_buffer; struct vstor_packet vstor_packet; } ;
struct hv_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ INQUIRY ; 
 scalar_t__ MODE_SENSE ; 
 int SRB_STATUS_AUTOSENSE_VALID ; 
 int SRB_STATUS_SUCCESS ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,struct storvsc_cmd_request*,int,...) ; 
 struct storvsc_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storvsc_command_completion (struct storvsc_cmd_request*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void storvsc_on_io_completion(struct hv_device *device,
				  struct vstor_packet *vstor_packet,
				  struct storvsc_cmd_request *request)
{
	struct storvsc_device *stor_device;
	struct vstor_packet *stor_pkt;

	stor_device = hv_get_drvdata(device);
	stor_pkt = &request->vstor_packet;

	/*
	 * The current SCSI handling on the host side does
	 * not correctly handle:
	 * INQUIRY command with page code parameter set to 0x80
	 * MODE_SENSE command with cmd[2] == 0x1c
	 *
	 * Setup srb and scsi status so this won't be fatal.
	 * We do this so we can distinguish truly fatal failues
	 * (srb status == 0x4) and off-line the device in that case.
	 */

	if ((stor_pkt->vm_srb.cdb[0] == INQUIRY) ||
	   (stor_pkt->vm_srb.cdb[0] == MODE_SENSE)) {
		vstor_packet->vm_srb.scsi_status = 0;
		vstor_packet->vm_srb.srb_status = SRB_STATUS_SUCCESS;
	}


	/* Copy over the status...etc */
	stor_pkt->vm_srb.scsi_status = vstor_packet->vm_srb.scsi_status;
	stor_pkt->vm_srb.srb_status = vstor_packet->vm_srb.srb_status;
	stor_pkt->vm_srb.sense_info_length =
	vstor_packet->vm_srb.sense_info_length;

	if (vstor_packet->vm_srb.scsi_status != 0 ||
		vstor_packet->vm_srb.srb_status != SRB_STATUS_SUCCESS){
		dev_warn(&device->device,
			 "cmd 0x%x scsi status 0x%x srb status 0x%x\n",
			 stor_pkt->vm_srb.cdb[0],
			 vstor_packet->vm_srb.scsi_status,
			 vstor_packet->vm_srb.srb_status);
	}

	if ((vstor_packet->vm_srb.scsi_status & 0xFF) == 0x02) {
		/* CHECK_CONDITION */
		if (vstor_packet->vm_srb.srb_status &
			SRB_STATUS_AUTOSENSE_VALID) {
			/* autosense data available */
			dev_warn(&device->device,
				 "stor pkt %p autosense data valid - len %d\n",
				 request,
				 vstor_packet->vm_srb.sense_info_length);

			memcpy(request->sense_buffer,
			       vstor_packet->vm_srb.sense_data,
			       vstor_packet->vm_srb.sense_info_length);

		}
	}

	stor_pkt->vm_srb.data_transfer_length =
	vstor_packet->vm_srb.data_transfer_length;

	storvsc_command_completion(request);

	if (atomic_dec_and_test(&stor_device->num_outstanding_req) &&
		stor_device->drain_notify)
		wake_up(&stor_device->waiting_to_drain);


}