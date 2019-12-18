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
struct ap_queue_status {int response_code; int /*<<< orphan*/  queue_empty; } ;
typedef  int /*<<< orphan*/  ap_qid_t ;

/* Variables and functions */
#define  AP_RESPONSE_NORMAL 130 
#define  AP_RESPONSE_NO_PENDING_REPLY 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int EBUSY ; 
 int ENODEV ; 
 int ENOENT ; 
 struct ap_queue_status __ap_recv (int /*<<< orphan*/ ,unsigned long long*,void*,size_t) ; 

int ap_recv(ap_qid_t qid, unsigned long long *psmid, void *msg, size_t length)
{
	struct ap_queue_status status;

	status = __ap_recv(qid, psmid, msg, length);
	switch (status.response_code) {
	case AP_RESPONSE_NORMAL:
		return 0;
	case AP_RESPONSE_NO_PENDING_REPLY:
		if (status.queue_empty)
			return -ENOENT;
		return -EBUSY;
	case AP_RESPONSE_RESET_IN_PROGRESS:
		return -EBUSY;
	default:
		return -ENODEV;
	}
}