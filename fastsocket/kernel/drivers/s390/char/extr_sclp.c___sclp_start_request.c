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
struct sclp_req {int /*<<< orphan*/  status; int /*<<< orphan*/  start_count; int /*<<< orphan*/  sccb; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 int SCLP_BUSY_INTERVAL ; 
 int /*<<< orphan*/  SCLP_REQ_FAILED ; 
 int /*<<< orphan*/  SCLP_REQ_RUNNING ; 
 int SCLP_RETRY_INTERVAL ; 
 int /*<<< orphan*/  __sclp_set_request_timer (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_request_timeout ; 
 int /*<<< orphan*/  sclp_request_timer ; 
 scalar_t__ sclp_running_state ; 
 scalar_t__ sclp_running_state_idle ; 
 scalar_t__ sclp_running_state_running ; 
 int sclp_service_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__sclp_start_request(struct sclp_req *req)
{
	int rc;

	if (sclp_running_state != sclp_running_state_idle)
		return 0;
	del_timer(&sclp_request_timer);
	rc = sclp_service_call(req->command, req->sccb);
	req->start_count++;

	if (rc == 0) {
		/* Sucessfully started request */
		req->status = SCLP_REQ_RUNNING;
		sclp_running_state = sclp_running_state_running;
		__sclp_set_request_timer(SCLP_RETRY_INTERVAL * HZ,
					 sclp_request_timeout, 1);
		return 0;
	} else if (rc == -EBUSY) {
		/* Try again later */
		__sclp_set_request_timer(SCLP_BUSY_INTERVAL * HZ,
					 sclp_request_timeout, 0);
		return 0;
	}
	/* Request failed */
	req->status = SCLP_REQ_FAILED;
	return rc;
}