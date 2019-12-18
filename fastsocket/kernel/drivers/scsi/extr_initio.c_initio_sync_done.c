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
struct initio_host {int* msg; scalar_t__ addr; TYPE_1__* active_tc; } ;
struct TYPE_2__ {int js_period; int sconfig0; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCF_SYNC_DONE ; 
 int TSC_ALT_PERIOD ; 
 scalar_t__ TUL_SConfig ; 
 scalar_t__ TUL_SPeriod ; 
 int* initio_rate_tbl ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int initio_sync_done(struct initio_host * host)
{
	int i;

	host->active_tc->flags |= TCF_SYNC_DONE;

	if (host->msg[3]) {
		host->active_tc->js_period |= host->msg[3];
		for (i = 0; i < 8; i++) {
			if (initio_rate_tbl[i] >= host->msg[2])	/* pick the big one */
				break;
		}
		host->active_tc->js_period |= (i << 4);
		host->active_tc->sconfig0 |= TSC_ALT_PERIOD;
	}
	outb(host->active_tc->sconfig0, host->addr + TUL_SConfig);
	outb(host->active_tc->js_period, host->addr + TUL_SPeriod);

	return -1;
}