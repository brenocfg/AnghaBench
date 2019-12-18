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
struct memstick_host {int /*<<< orphan*/  (* request ) (struct memstick_host*) ;TYPE_1__* card; int /*<<< orphan*/  retries; } ;
struct TYPE_2__ {int /*<<< orphan*/  mrq_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_COMPLETION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_retries ; 
 int /*<<< orphan*/  stub1 (struct memstick_host*) ; 

void memstick_new_req(struct memstick_host *host)
{
	if (host->card) {
		host->retries = cmd_retries;
		INIT_COMPLETION(host->card->mrq_complete);
		host->request(host);
	}
}