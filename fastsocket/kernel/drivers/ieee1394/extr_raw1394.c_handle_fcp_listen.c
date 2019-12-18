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
struct TYPE_2__ {scalar_t__ length; void* error; int /*<<< orphan*/  recvb; scalar_t__ misc; } ;
struct pending_request {TYPE_1__ req; } ;
struct file_info {int /*<<< orphan*/ * fcp_buffer; } ;

/* Variables and functions */
 void* RAW1394_ERROR_ALREADY ; 
 int /*<<< orphan*/ * int2ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_complete_req (struct pending_request*) ; 

__attribute__((used)) static void handle_fcp_listen(struct file_info *fi, struct pending_request *req)
{
	if (req->req.misc) {
		if (fi->fcp_buffer) {
			req->req.error = RAW1394_ERROR_ALREADY;
		} else {
			fi->fcp_buffer = int2ptr(req->req.recvb);
		}
	} else {
		if (!fi->fcp_buffer) {
			req->req.error = RAW1394_ERROR_ALREADY;
		} else {
			fi->fcp_buffer = NULL;
		}
	}

	req->req.length = 0;
	queue_complete_req(req);
}