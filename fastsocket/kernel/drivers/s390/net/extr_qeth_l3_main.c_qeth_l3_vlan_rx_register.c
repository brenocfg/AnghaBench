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
struct vlan_group {int dummy; } ;
struct qeth_card {int /*<<< orphan*/  vlanlock; struct vlan_group* vlangrp; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qeth_l3_vlan_rx_register(struct net_device *dev,
			struct vlan_group *grp)
{
	struct qeth_card *card = dev->ml_priv;
	unsigned long flags;

	QETH_DBF_TEXT(TRACE, 4, "vlanreg");
	spin_lock_irqsave(&card->vlanlock, flags);
	card->vlangrp = grp;
	spin_unlock_irqrestore(&card->vlanlock, flags);
}