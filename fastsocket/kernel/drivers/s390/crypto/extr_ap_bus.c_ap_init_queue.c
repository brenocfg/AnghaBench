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
 int AP_MAX_RESET ; 
 int /*<<< orphan*/  AP_QID_DEVICE (int /*<<< orphan*/ ) ; 
#define  AP_RESPONSE_BUSY 133 
#define  AP_RESPONSE_CHECKSTOPPED 132 
#define  AP_RESPONSE_DECONFIGURED 131 
#define  AP_RESPONSE_NORMAL 130 
#define  AP_RESPONSE_Q_NOT_AVAIL 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  ap_interrupt_indicator ; 
 int ap_queue_enable_interruption (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ap_queue_status ap_reset_queue (int /*<<< orphan*/ ) ; 
 struct ap_queue_status ap_test_queue (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ ap_using_interrupts () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ap_init_queue(ap_qid_t qid)
{
	struct ap_queue_status status;
	int rc, dummy, i;

	rc = -ENODEV;
	status = ap_reset_queue(qid);
	for (i = 0; i < AP_MAX_RESET; i++) {
		switch (status.response_code) {
		case AP_RESPONSE_NORMAL:
			if (status.queue_empty)
				rc = 0;
			break;
		case AP_RESPONSE_Q_NOT_AVAIL:
		case AP_RESPONSE_DECONFIGURED:
		case AP_RESPONSE_CHECKSTOPPED:
			i = AP_MAX_RESET;	/* return with -ENODEV */
			break;
		case AP_RESPONSE_RESET_IN_PROGRESS:
			rc = -EBUSY;
		case AP_RESPONSE_BUSY:
		default:
			break;
		}
		if (rc != -ENODEV && rc != -EBUSY)
			break;
		if (i < AP_MAX_RESET - 1) {
			udelay(5);
			status = ap_test_queue(qid, &dummy, &dummy);
		}
	}
	if (rc == 0 && ap_using_interrupts()) {
		rc = ap_queue_enable_interruption(qid, ap_interrupt_indicator);
		/* If interruption mode is supported by the machine,
		* but an AP can not be enabled for interruption then
		* the AP will be discarded.    */
		if (rc)
			pr_err("Registering adapter interrupts for "
			       "AP %d failed\n", AP_QID_DEVICE(qid));
	}
	return rc;
}