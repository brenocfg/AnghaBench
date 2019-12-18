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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct qeth_card {TYPE_1__ stats; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 

void qeth_tx_timeout(struct net_device *dev)
{
	struct qeth_card *card;

	QETH_DBF_TEXT(TRACE, 4, "txtimeo");
	card = dev->ml_priv;
	card->stats.tx_errors++;
	qeth_schedule_recovery(card);
}