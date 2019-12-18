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
struct mmc_request {int dummy; } ;
struct atmel_mci_slot {int /*<<< orphan*/  queue_node; struct mmc_request* mrq; TYPE_1__* mmc; } ;
struct atmel_mci {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 scalar_t__ STATE_IDLE ; 
 scalar_t__ STATE_SENDING_CMD ; 
 int /*<<< orphan*/  atmci_start_request (struct atmel_mci*,struct atmel_mci_slot*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atmci_queue_request(struct atmel_mci *host,
		struct atmel_mci_slot *slot, struct mmc_request *mrq)
{
	dev_vdbg(&slot->mmc->class_dev, "queue request: state=%d\n",
			host->state);

	spin_lock_bh(&host->lock);
	slot->mrq = mrq;
	if (host->state == STATE_IDLE) {
		host->state = STATE_SENDING_CMD;
		atmci_start_request(host, slot);
	} else {
		list_add_tail(&slot->queue_node, &host->queue);
	}
	spin_unlock_bh(&host->lock);
}