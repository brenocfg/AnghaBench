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
struct TYPE_4__ {int /*<<< orphan*/  path_id; } ;
struct vstor_packet {TYPE_2__ vm_srb; int /*<<< orphan*/  flags; int /*<<< orphan*/  operation; } ;
struct storvsc_cmd_request {int /*<<< orphan*/  wait_event; struct vstor_packet vstor_packet; } ;
struct storvsc_device {struct storvsc_cmd_request reset_request; int /*<<< orphan*/  path_id; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct hv_host_device {struct hv_device* dev; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int HZ ; 
 int /*<<< orphan*/  REQUEST_COMPLETION_FLAG ; 
 int SUCCESS ; 
 int TIMEOUT_ERROR ; 
 int /*<<< orphan*/  VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  VSTOR_OPERATION_RESET_BUS ; 
 struct storvsc_device* get_out_stor_device (struct hv_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct hv_host_device* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storvsc_wait_to_drain (struct storvsc_device*) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct vstor_packet*,scalar_t__,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vmscsi_size_delta ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int storvsc_host_reset_handler(struct scsi_cmnd *scmnd)
{
	struct hv_host_device *host_dev = shost_priv(scmnd->device->host);
	struct hv_device *device = host_dev->dev;

	struct storvsc_device *stor_device;
	struct storvsc_cmd_request *request;
	struct vstor_packet *vstor_packet;
	int ret, t;


	stor_device = get_out_stor_device(device);
	if (!stor_device)
		return FAILED;

	request = &stor_device->reset_request;
	vstor_packet = &request->vstor_packet;

	init_completion(&request->wait_event);

	vstor_packet->operation = VSTOR_OPERATION_RESET_BUS;
	vstor_packet->flags = REQUEST_COMPLETION_FLAG;
	vstor_packet->vm_srb.path_id = stor_device->path_id;

	ret = vmbus_sendpacket(device->channel, vstor_packet,
			       (sizeof(struct vstor_packet) -
				vmscsi_size_delta),
			       (unsigned long)&stor_device->reset_request,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	if (ret != 0)
		return FAILED;

	t = wait_for_completion_timeout(&request->wait_event, 5*HZ);
	if (t == 0)
		return TIMEOUT_ERROR;


	/*
	 * At this point, all outstanding requests in the adapter
	 * should have been flushed out and return to us
	 * There is a potential race here where the host may be in
	 * the process of responding when we return from here.
	 * Just wait for all in-transit packets to be accounted for
	 * before we return from here.
	 */
	storvsc_wait_to_drain(stor_device);

	return SUCCESS;
}