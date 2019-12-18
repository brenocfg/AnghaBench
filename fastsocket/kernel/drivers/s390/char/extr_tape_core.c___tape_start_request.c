#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tape_request {int op; int /*<<< orphan*/  list; int /*<<< orphan*/  status; int /*<<< orphan*/  device; } ;
struct tape_device {int /*<<< orphan*/  req_queue; int /*<<< orphan*/  tape_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_LH (int,char*,struct tape_request*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  TAPE_REQUEST_QUEUED ; 
#define  TO_ASSIGN 132 
#define  TO_MSEN 131 
#define  TO_RDC 130 
#define  TO_READ_ATTMSG 129 
#define  TO_UNASSIGN 128 
 int /*<<< orphan*/  TS_BLKUSE ; 
 int /*<<< orphan*/  TS_INIT ; 
 int /*<<< orphan*/  TS_IN_USE ; 
 int /*<<< orphan*/  TS_UNUSED ; 
 int __tape_start_io (struct tape_device*,struct tape_request*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tape_get_device_reference (struct tape_device*) ; 

__attribute__((used)) static int
__tape_start_request(struct tape_device *device, struct tape_request *request)
{
	int rc;

	switch (request->op) {
		case TO_MSEN:
		case TO_ASSIGN:
		case TO_UNASSIGN:
		case TO_READ_ATTMSG:
		case TO_RDC:
			if (device->tape_state == TS_INIT)
				break;
			if (device->tape_state == TS_UNUSED)
				break;
		default:
			if (device->tape_state == TS_BLKUSE)
				break;
			if (device->tape_state != TS_IN_USE)
				return -ENODEV;
	}

	/* Increase use count of device for the added request. */
	request->device = tape_get_device_reference(device);

	if (list_empty(&device->req_queue)) {
		/* No other requests are on the queue. Start this one. */
		rc = __tape_start_io(device, request);
		if (rc)
			return rc;

		DBF_LH(5, "Request %p added for execution.\n", request);
		list_add(&request->list, &device->req_queue);
	} else {
		DBF_LH(5, "Request %p add to queue.\n", request);
		request->status = TAPE_REQUEST_QUEUED;
		list_add_tail(&request->list, &device->req_queue);
	}
	return 0;
}