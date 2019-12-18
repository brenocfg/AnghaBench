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
struct TYPE_2__ {scalar_t__ type; int misc; scalar_t__ length; int /*<<< orphan*/  error; int /*<<< orphan*/  generation; } ;
struct pending_request {TYPE_1__ req; } ;
struct file_info {int protocol_version; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAW1394_ERROR_COMPAT ; 
 int /*<<< orphan*/  RAW1394_ERROR_NONE ; 
 int /*<<< orphan*/  RAW1394_ERROR_STATE_ORDER ; 
#define  RAW1394_KERNELAPI_VERSION 128 
 scalar_t__ RAW1394_REQ_INITIALIZE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialized ; 
 int /*<<< orphan*/  internal_generation ; 
 int /*<<< orphan*/  queue_complete_req (struct pending_request*) ; 

__attribute__((used)) static int state_opened(struct file_info *fi, struct pending_request *req)
{
	if (req->req.type == RAW1394_REQ_INITIALIZE) {
		switch (req->req.misc) {
		case RAW1394_KERNELAPI_VERSION:
		case 3:
			fi->state = initialized;
			fi->protocol_version = req->req.misc;
			req->req.error = RAW1394_ERROR_NONE;
			req->req.generation = atomic_read(&internal_generation);
			break;

		default:
			req->req.error = RAW1394_ERROR_COMPAT;
			req->req.misc = RAW1394_KERNELAPI_VERSION;
		}
	} else {
		req->req.error = RAW1394_ERROR_STATE_ORDER;
	}

	req->req.length = 0;
	queue_complete_req(req);
	return 0;
}