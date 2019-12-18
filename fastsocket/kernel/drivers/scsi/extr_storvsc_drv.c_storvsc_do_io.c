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
struct TYPE_3__ {scalar_t__ data_transfer_length; int /*<<< orphan*/  sense_info_length; scalar_t__ length; } ;
struct vstor_packet {int /*<<< orphan*/  operation; TYPE_1__ vm_srb; int /*<<< orphan*/  flags; } ;
struct vmscsi_request {int dummy; } ;
struct vmbus_channel {int dummy; } ;
struct storvsc_device {int /*<<< orphan*/  num_outstanding_req; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct storvsc_cmd_request {TYPE_2__ data_buffer; struct hv_device* device; struct vstor_packet vstor_packet; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  REQUEST_COMPLETION_FLAG ; 
 int /*<<< orphan*/  VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  VSTOR_OPERATION_EXECUTE_SRB ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct storvsc_device* get_out_stor_device (struct hv_device*) ; 
 int /*<<< orphan*/  sense_buffer_size ; 
 struct vmbus_channel* vmbus_get_outgoing_channel (int /*<<< orphan*/ ) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct vstor_packet*,scalar_t__,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmbus_sendpacket_multipagebuffer (struct vmbus_channel*,TYPE_2__*,struct vstor_packet*,scalar_t__,unsigned long) ; 
 scalar_t__ vmscsi_size_delta ; 

__attribute__((used)) static int storvsc_do_io(struct hv_device *device,
			      struct storvsc_cmd_request *request)
{
	struct storvsc_device *stor_device;
	struct vstor_packet *vstor_packet;
	struct vmbus_channel *outgoing_channel;
	int ret = 0;

	vstor_packet = &request->vstor_packet;
	stor_device = get_out_stor_device(device);

	if (!stor_device)
		return -ENODEV;


	request->device  = device;
	/*
	 * Select an an appropriate channel to send the request out.
	 */

	outgoing_channel = vmbus_get_outgoing_channel(device->channel);


	vstor_packet->flags |= REQUEST_COMPLETION_FLAG;

	vstor_packet->vm_srb.length = (sizeof(struct vmscsi_request) -
					vmscsi_size_delta);


	vstor_packet->vm_srb.sense_info_length = sense_buffer_size;


	vstor_packet->vm_srb.data_transfer_length =
	request->data_buffer.len;

	vstor_packet->operation = VSTOR_OPERATION_EXECUTE_SRB;

	if (request->data_buffer.len) {
		ret = vmbus_sendpacket_multipagebuffer(outgoing_channel,
				&request->data_buffer,
				vstor_packet,
				(sizeof(struct vstor_packet) -
				vmscsi_size_delta),
				(unsigned long)request);
	} else {
		ret = vmbus_sendpacket(device->channel, vstor_packet,
			       (sizeof(struct vstor_packet) -
				vmscsi_size_delta),
			       (unsigned long)request,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	}

	if (ret != 0)
		return ret;

	atomic_inc(&stor_device->num_outstanding_req);

	return ret;
}