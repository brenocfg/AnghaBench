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
struct packet_type {scalar_t__ type; } ;
struct bonding {struct packet_type arp_mon_pt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_remove_pack (struct packet_type*) ; 

void bond_unregister_arp(struct bonding *bond)
{
	struct packet_type *pt = &bond->arp_mon_pt;

	dev_remove_pack(pt);
	pt->type = 0;
}