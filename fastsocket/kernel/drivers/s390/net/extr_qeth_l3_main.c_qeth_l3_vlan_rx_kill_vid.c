#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qeth_card {int /*<<< orphan*/  dev; int /*<<< orphan*/  vlanlock; int /*<<< orphan*/  vlangrp; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,unsigned short) ; 
 int /*<<< orphan*/  QETH_RECOVER_THREAD ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  qeth_l3_free_vlan_addresses (struct qeth_card*,unsigned short) ; 
 int /*<<< orphan*/  qeth_l3_set_multicast_list (int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_wait_for_threads (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vlan_group_set_device (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_l3_vlan_rx_kill_vid(struct net_device *dev, unsigned short vid)
{
	struct qeth_card *card = dev->ml_priv;
	unsigned long flags;

	QETH_DBF_TEXT_(TRACE, 4, "kid:%d", vid);
	if (qeth_wait_for_threads(card, QETH_RECOVER_THREAD)) {
		QETH_DBF_TEXT(TRACE, 3, "kidREC");
		return;
	}
	spin_lock_irqsave(&card->vlanlock, flags);
	/* unregister IP addresses of vlan device */
	qeth_l3_free_vlan_addresses(card, vid);
	vlan_group_set_device(card->vlangrp, vid, NULL);
	spin_unlock_irqrestore(&card->vlanlock, flags);
	qeth_l3_set_multicast_list(card->dev);
}