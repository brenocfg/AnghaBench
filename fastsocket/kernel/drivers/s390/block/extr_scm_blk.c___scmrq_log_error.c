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
struct scm_request {int /*<<< orphan*/  error; scalar_t__ retries; struct aob* aob; } ;
struct aob {int /*<<< orphan*/  response; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  SCM_LOG (int,char*) ; 
 int /*<<< orphan*/  SCM_LOG_HEX (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __scmrq_log_error(struct scm_request *scmrq)
{
	struct aob *aob = scmrq->aob;

	if (scmrq->error == -ETIMEDOUT)
		SCM_LOG(1, "Request timeout");
	else {
		SCM_LOG(1, "Request error");
		SCM_LOG_HEX(1, &aob->response, sizeof(aob->response));
	}
	if (scmrq->retries)
		SCM_LOG(1, "Retry request");
	else
		pr_err("An I/O operation to SCM failed with rc=%d\n",
		       scmrq->error);
}