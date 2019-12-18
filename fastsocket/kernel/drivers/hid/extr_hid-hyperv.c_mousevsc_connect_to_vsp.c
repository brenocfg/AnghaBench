#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct synthhid_protocol_request {int dummy; } ;
struct pipe_prt_msg {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  approved; } ;
struct TYPE_6__ {int /*<<< orphan*/  version; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_2__ version_requested; TYPE_1__ header; } ;
struct mousevsc_prt_msg {int size; TYPE_4__ response; TYPE_3__ request; int /*<<< orphan*/  type; } ;
struct mousevsc_dev {int dev_info_status; int /*<<< orphan*/  wait_event; struct mousevsc_prt_msg protocol_resp; struct mousevsc_prt_msg protocol_req; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  PIPE_MESSAGE_DATA ; 
 int /*<<< orphan*/  SYNTHHID_INPUT_VERSION ; 
 int /*<<< orphan*/  SYNTH_HID_PROTOCOL_REQUEST ; 
 int /*<<< orphan*/  VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 struct mousevsc_dev* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  memset (struct mousevsc_prt_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct mousevsc_prt_msg*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mousevsc_connect_to_vsp(struct hv_device *device)
{
	int ret = 0;
	int t;
	struct mousevsc_dev *input_dev = hv_get_drvdata(device);
	struct mousevsc_prt_msg *request;
	struct mousevsc_prt_msg *response;

	request = &input_dev->protocol_req;
	memset(request, 0, sizeof(struct mousevsc_prt_msg));

	request->type = PIPE_MESSAGE_DATA;
	request->size = sizeof(struct synthhid_protocol_request);
	request->request.header.type = SYNTH_HID_PROTOCOL_REQUEST;
	request->request.header.size = sizeof(unsigned int);
	request->request.version_requested.version = SYNTHHID_INPUT_VERSION;

	ret = vmbus_sendpacket(device->channel, request,
				sizeof(struct pipe_prt_msg) -
				sizeof(unsigned char) +
				sizeof(struct synthhid_protocol_request),
				(unsigned long)request,
				VM_PKT_DATA_INBAND,
				VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	if (ret)
		goto cleanup;

	t = wait_for_completion_timeout(&input_dev->wait_event, 5*HZ);
	if (!t) {
		ret = -ETIMEDOUT;
		goto cleanup;
	}

	response = &input_dev->protocol_resp;

	if (!response->response.approved) {
		pr_err("synthhid protocol request failed (version %d)\n",
		       SYNTHHID_INPUT_VERSION);
		ret = -ENODEV;
		goto cleanup;
	}

	t = wait_for_completion_timeout(&input_dev->wait_event, 5*HZ);
	if (!t) {
		ret = -ETIMEDOUT;
		goto cleanup;
	}

	/*
	 * We should have gotten the device attr, hid desc and report
	 * desc at this point
	 */
	ret = input_dev->dev_info_status;

cleanup:
	return ret;
}