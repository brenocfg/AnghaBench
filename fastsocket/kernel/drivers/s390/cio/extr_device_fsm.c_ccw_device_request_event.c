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
struct ccw_device {int dummy; } ;
typedef  enum dev_event { ____Placeholder_dev_event } dev_event ;

/* Variables and functions */
#define  DEV_EVENT_INTERRUPT 130 
#define  DEV_EVENT_NOTOPER 129 
#define  DEV_EVENT_TIMEOUT 128 
 int /*<<< orphan*/  ccw_request_handler (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_request_notoper (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_request_timeout (struct ccw_device*) ; 

__attribute__((used)) static void ccw_device_request_event(struct ccw_device *cdev, enum dev_event e)
{
	switch (e) {
	case DEV_EVENT_NOTOPER:
		ccw_request_notoper(cdev);
		break;
	case DEV_EVENT_INTERRUPT:
		ccw_request_handler(cdev);
		break;
	case DEV_EVENT_TIMEOUT:
		ccw_request_timeout(cdev);
		break;
	default:
		break;
	}
}