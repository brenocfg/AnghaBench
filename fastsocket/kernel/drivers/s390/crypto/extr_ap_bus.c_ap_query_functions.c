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
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 struct ap_queue_status __ap_query_functions (int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ ap_queue_status_invalid_test (struct ap_queue_status*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ap_query_functions(ap_qid_t qid, unsigned int *functions)
{
#ifdef CONFIG_64BIT
	struct ap_queue_status status;
	int i;
	status = __ap_query_functions(qid, functions);

	for (i = 0; i < AP_MAX_RESET; i++) {
		if (ap_queue_status_invalid_test(&status))
			return -ENODEV;

		switch (status.response_code) {
		case AP_RESPONSE_NORMAL:
			return 0;
		case AP_RESPONSE_RESET_IN_PROGRESS:
		case AP_RESPONSE_BUSY:
			break;
		case AP_RESPONSE_Q_NOT_AVAIL:
		case AP_RESPONSE_DECONFIGURED:
		case AP_RESPONSE_CHECKSTOPPED:
		case AP_RESPONSE_INVALID_ADDRESS:
			return -ENODEV;
		case AP_RESPONSE_OTHERWISE_CHANGED:
			break;
		default:
			break;
		}
		if (i < AP_MAX_RESET - 1) {
			udelay(5);
			status = __ap_query_functions(qid, functions);
		}
	}
	return -EBUSY;
#else
	return -EINVAL;
#endif
}