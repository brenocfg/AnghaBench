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
struct mmc_request {int /*<<< orphan*/  done; int /*<<< orphan*/ * done_data; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete ; 
 int /*<<< orphan*/  mmc_start_request (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_wait_done ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void mmc_wait_for_req(struct mmc_host *host, struct mmc_request *mrq)
{
	DECLARE_COMPLETION_ONSTACK(complete);

	mrq->done_data = &complete;
	mrq->done = mmc_wait_done;

	mmc_start_request(host, mrq);

	wait_for_completion(&complete);
}