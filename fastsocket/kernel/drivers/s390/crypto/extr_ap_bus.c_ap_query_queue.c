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
struct ap_queue_status {int response_code; } ;
typedef  int /*<<< orphan*/  ap_qid_t ;

/* Variables and functions */
 int AP_MAX_RESET ; 
#define  AP_RESPONSE_BUSY 135 
#define  AP_RESPONSE_CHECKSTOPPED 134 
#define  AP_RESPONSE_DECONFIGURED 133 
#define  AP_RESPONSE_INVALID_ADDRESS 132 
#define  AP_RESPONSE_NORMAL 131 
#define  AP_RESPONSE_OTHERWISE_CHANGED 130 
#define  AP_RESPONSE_Q_NOT_AVAIL 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int /*<<< orphan*/  BUG () ; 
 int EBUSY ; 
 int ENODEV ; 
 struct ap_queue_status ap_test_queue (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ap_query_queue(ap_qid_t qid, int *queue_depth, int *device_type)
{
	struct ap_queue_status status;
	int t_depth, t_device_type, rc, i;

	rc = -EBUSY;
	for (i = 0; i < AP_MAX_RESET; i++) {
		status = ap_test_queue(qid, &t_depth, &t_device_type);
		switch (status.response_code) {
		case AP_RESPONSE_NORMAL:
			*queue_depth = t_depth + 1;
			*device_type = t_device_type;
			rc = 0;
			break;
		case AP_RESPONSE_Q_NOT_AVAIL:
			rc = -ENODEV;
			break;
		case AP_RESPONSE_RESET_IN_PROGRESS:
			break;
		case AP_RESPONSE_DECONFIGURED:
			rc = -ENODEV;
			break;
		case AP_RESPONSE_CHECKSTOPPED:
			rc = -ENODEV;
			break;
		case AP_RESPONSE_INVALID_ADDRESS:
			rc = -ENODEV;
			break;
		case AP_RESPONSE_OTHERWISE_CHANGED:
			break;
		case AP_RESPONSE_BUSY:
			break;
		default:
			BUG();
		}
		if (rc != -EBUSY)
			break;
		if (i < AP_MAX_RESET - 1)
			udelay(5);
	}
	return rc;
}