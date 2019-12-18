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
struct packet_type {int /*<<< orphan*/  func; int /*<<< orphan*/  dev; scalar_t__ type; } ;
struct bonding {int /*<<< orphan*/  dev; struct packet_type arp_mon_pt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  bond_arp_rcv ; 
 int /*<<< orphan*/  dev_add_pack (struct packet_type*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

void bond_register_arp(struct bonding *bond)
{
	struct packet_type *pt = &bond->arp_mon_pt;

	if (pt->type)
		return;

	pt->type = htons(ETH_P_ARP);
	pt->dev = bond->dev;
	pt->func = bond_arp_rcv;
	dev_add_pack(pt);
}