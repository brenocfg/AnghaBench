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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ misc; } ;
struct pending_request {TYPE_1__ req; } ;
struct file_info {scalar_t__ notification; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*,char*) ; 
 int EINVAL ; 
 scalar_t__ RAW1394_NOTIFY_OFF ; 
 scalar_t__ RAW1394_NOTIFY_ON ; 
 int /*<<< orphan*/  free_pending_request (struct pending_request*) ; 

__attribute__((used)) static int reset_notification(struct file_info *fi, struct pending_request *req)
{
	DBGMSG("reset_notification called - switch %s ",
	       (req->req.misc == RAW1394_NOTIFY_OFF) ? "OFF" : "ON");
	if ((req->req.misc == RAW1394_NOTIFY_OFF) ||
	    (req->req.misc == RAW1394_NOTIFY_ON)) {
		fi->notification = (u8) req->req.misc;
		free_pending_request(req);	/* we have to free the request, because we queue no response, and therefore nobody will free it */
		return 0;
	}
	/* error EINVAL (22) invalid argument */
	return (-EINVAL);
}