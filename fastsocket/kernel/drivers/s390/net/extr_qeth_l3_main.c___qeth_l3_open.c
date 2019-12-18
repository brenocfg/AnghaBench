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
struct TYPE_2__ {int /*<<< orphan*/  ccwdev; int /*<<< orphan*/  state; } ;
struct qeth_card {scalar_t__ state; int /*<<< orphan*/  napi; TYPE_1__ data; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_SOFTSETUP ; 
 scalar_t__ CARD_STATE_UP ; 
 int /*<<< orphan*/  CH_STATE_UP ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ qdio_stop_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __qeth_l3_open(struct net_device *dev)
{
	struct qeth_card *card = dev->ml_priv;
	int rc = 0;

	QETH_DBF_TEXT(TRACE, 4, "qethopen");
	if (card->state == CARD_STATE_UP)
		return 0;
	if (card->state != CARD_STATE_SOFTSETUP)
		return -ENODEV;
	card->data.state = CH_STATE_UP;
	card->state = CARD_STATE_UP;
	netif_start_queue(dev);

	if (qdio_stop_irq(card->data.ccwdev, 0) >= 0) {
		napi_enable(&card->napi);
		napi_schedule(&card->napi);
	} else
		rc = -EIO;
	return rc;
}