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
struct TYPE_2__ {scalar_t__ hwtrap; } ;
struct qeth_card {scalar_t__ state; int /*<<< orphan*/  gdev; TYPE_1__ info; int /*<<< orphan*/  wait_q; scalar_t__ dev; } ;
struct ccwgroup_device {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_UP ; 
 scalar_t__ CCWGROUP_OFFLINE ; 
 int /*<<< orphan*/  QETH_DIAGS_TRAP_DISARM ; 
 int /*<<< orphan*/  __qeth_l3_set_offline (int /*<<< orphan*/ ,int) ; 
 struct qeth_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (scalar_t__) ; 
 int /*<<< orphan*/  qeth_hw_trap (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_set_allowed_threads (struct qeth_card*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qeth_threads_running (struct qeth_card*,int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qeth_l3_pm_suspend(struct ccwgroup_device *gdev)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);

	if (card->dev)
		netif_device_detach(card->dev);
	qeth_set_allowed_threads(card, 0, 1);
	wait_event(card->wait_q, qeth_threads_running(card, 0xffffffff) == 0);
	if (gdev->state == CCWGROUP_OFFLINE)
		return 0;
	if (card->state == CARD_STATE_UP) {
		if (card->info.hwtrap)
			qeth_hw_trap(card, QETH_DIAGS_TRAP_DISARM);
		__qeth_l3_set_offline(card->gdev, 1);
	} else
		__qeth_l3_set_offline(card->gdev, 0);
	return 0;
}