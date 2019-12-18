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
struct qeth_card {int /*<<< orphan*/  vlangrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  qeth_l3_free_vlan_addresses4 (struct qeth_card*,unsigned short) ; 
 int /*<<< orphan*/  qeth_l3_free_vlan_addresses6 (struct qeth_card*,unsigned short) ; 

__attribute__((used)) static void qeth_l3_free_vlan_addresses(struct qeth_card *card,
			unsigned short vid)
{
	if (!card->vlangrp)
		return;
	qeth_l3_free_vlan_addresses4(card, vid);
	qeth_l3_free_vlan_addresses6(card, vid);
}