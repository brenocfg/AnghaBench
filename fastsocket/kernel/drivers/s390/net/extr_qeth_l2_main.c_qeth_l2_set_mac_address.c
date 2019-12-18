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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct qeth_card {TYPE_2__* dev; TYPE_1__ info; } ;
struct net_device {struct qeth_card* ml_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_BUS_ID (struct qeth_card*) ; 
 int EOPNOTSUPP ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  OSA_ADDR_LEN ; 
 scalar_t__ QETH_CARD_TYPE_OSM ; 
 scalar_t__ QETH_CARD_TYPE_OSN ; 
 scalar_t__ QETH_CARD_TYPE_OSX ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ QETH_REAL_CARD ; 
 int /*<<< orphan*/  QETH_RECOVER_THREAD ; 
 int /*<<< orphan*/  TRACE ; 
 int qeth_l2_send_delmac (struct qeth_card*,int /*<<< orphan*/ *) ; 
 int qeth_l2_send_setmac (struct qeth_card*,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_l2_verify_dev (struct net_device*) ; 
 scalar_t__ qeth_wait_for_threads (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l2_set_mac_address(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;
	struct qeth_card *card = dev->ml_priv;
	int rc = 0;

	QETH_DBF_TEXT(TRACE, 3, "setmac");

	if (qeth_l2_verify_dev(dev) != QETH_REAL_CARD) {
		QETH_DBF_TEXT(TRACE, 3, "setmcINV");
		return -EOPNOTSUPP;
	}

	if (card->info.type == QETH_CARD_TYPE_OSN ||
	    card->info.type == QETH_CARD_TYPE_OSM ||
	    card->info.type == QETH_CARD_TYPE_OSX) {
		QETH_DBF_TEXT(TRACE, 3, "setmcTYP");
		return -EOPNOTSUPP;
	}
	QETH_DBF_TEXT_(TRACE, 3, "%s", CARD_BUS_ID(card));
	QETH_DBF_HEX(TRACE, 3, addr->sa_data, OSA_ADDR_LEN);
	if (qeth_wait_for_threads(card, QETH_RECOVER_THREAD)) {
		QETH_DBF_TEXT(TRACE, 3, "setmcREC");
		return -ERESTARTSYS;
	}
	rc = qeth_l2_send_delmac(card, &card->dev->dev_addr[0]);
	if (!rc)
		rc = qeth_l2_send_setmac(card, addr->sa_data);
	return rc;
}