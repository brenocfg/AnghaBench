#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ccwdev; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {scalar_t__ type; int mac_bits; } ;
struct qeth_card {scalar_t__ state; int /*<<< orphan*/  napi; TYPE_2__ data; TYPE_1__ info; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_SOFTSETUP ; 
 scalar_t__ CARD_STATE_UP ; 
 int /*<<< orphan*/  CH_STATE_UP ; 
 int EIO ; 
 int ENODEV ; 
 int EPERM ; 
 scalar_t__ QETH_CARD_TYPE_OSN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int QETH_LAYER2_MAC_REGISTERED ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ qdio_stop_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __qeth_l2_open(struct net_device *dev)
{
	struct qeth_card *card = dev->ml_priv;
	int rc = 0;

	QETH_DBF_TEXT(TRACE, 4, "qethopen");
	if (card->state == CARD_STATE_UP)
		return 0;
	if (card->state != CARD_STATE_SOFTSETUP)
		return -ENODEV;

	if ((card->info.type != QETH_CARD_TYPE_OSN) &&
	     (!(card->info.mac_bits & QETH_LAYER2_MAC_REGISTERED))) {
		QETH_DBF_TEXT(TRACE, 4, "nomacadr");
		return -EPERM;
	}
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