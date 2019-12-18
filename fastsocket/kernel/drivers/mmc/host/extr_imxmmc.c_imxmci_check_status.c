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
struct imxmci_host {int present; int /*<<< orphan*/  timer; int /*<<< orphan*/  stuck_timeout; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  pending_events; int /*<<< orphan*/  mmc; TYPE_1__* pdata; } ;
struct TYPE_2__ {int (* card_present ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IMXMCI_PEND_CARD_XCHG_b ; 
 int /*<<< orphan*/  IMXMCI_PEND_DMA_DATA_b ; 
 int /*<<< orphan*/  IMXMCI_PEND_WAIT_RESP_b ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imxmci_check_status(unsigned long data)
{
	struct imxmci_host *host = (struct imxmci_host *)data;

	if (host->pdata && host->pdata->card_present &&
	    host->pdata->card_present(mmc_dev(host->mmc)) != host->present) {
		host->present ^= 1;
		dev_info(mmc_dev(host->mmc), "card %s\n",
		      host->present ? "inserted" : "removed");

		set_bit(IMXMCI_PEND_CARD_XCHG_b, &host->pending_events);
		tasklet_schedule(&host->tasklet);
	}

	if (test_bit(IMXMCI_PEND_WAIT_RESP_b, &host->pending_events) ||
	    test_bit(IMXMCI_PEND_DMA_DATA_b, &host->pending_events)) {
		atomic_inc(&host->stuck_timeout);
		if (atomic_read(&host->stuck_timeout) > 4)
			tasklet_schedule(&host->tasklet);
	} else {
		atomic_set(&host->stuck_timeout, 0);

	}

	mod_timer(&host->timer, jiffies + (HZ>>1));
}