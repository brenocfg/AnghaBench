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
struct smscore_device_t {int (* sendrequest_handler ) (int /*<<< orphan*/ ,void*,size_t) ;int /*<<< orphan*/  context; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  SMS_PROTOCOL_MAX_RAOUNDTRIP_MS ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_info (char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,void*,size_t) ; 
 scalar_t__ wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smscore_sendrequest_and_wait(struct smscore_device_t *coredev,
		void *buffer, size_t size, struct completion *completion) {
	int rc = coredev->sendrequest_handler(coredev->context, buffer, size);
	if (rc < 0) {
		sms_info("sendrequest returned error %d", rc);
		return rc;
	}

	return wait_for_completion_timeout(completion,
			msecs_to_jiffies(SMS_PROTOCOL_MAX_RAOUNDTRIP_MS)) ?
			0 : -ETIME;
}