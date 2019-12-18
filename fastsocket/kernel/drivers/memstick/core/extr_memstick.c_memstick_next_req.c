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
struct memstick_request {int error; } ;
struct memstick_host {int retries; TYPE_1__* card; } ;
struct TYPE_2__ {int (* next_request ) (TYPE_1__*,struct memstick_request**) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int cmd_retries ; 
 int stub1 (TYPE_1__*,struct memstick_request**) ; 

int memstick_next_req(struct memstick_host *host, struct memstick_request **mrq)
{
	int rc = -ENXIO;

	if ((*mrq) && (*mrq)->error && host->retries) {
		(*mrq)->error = rc;
		host->retries--;
		return 0;
	}

	if (host->card && host->card->next_request)
		rc = host->card->next_request(host->card, mrq);

	if (!rc)
		host->retries = cmd_retries > 1 ? cmd_retries - 1 : 1;
	else
		*mrq = NULL;

	return rc;
}