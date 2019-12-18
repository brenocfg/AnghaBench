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
struct lec_arp_table {scalar_t__ status; scalar_t__ no_tries; int /*<<< orphan*/  timer; int /*<<< orphan*/  mac_addr; TYPE_1__* priv; scalar_t__ is_rdesc; } ;
struct TYPE_2__ {scalar_t__ max_retry_count; } ;

/* Variables and functions */
 scalar_t__ ESI_ARP_PENDING ; 
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  l_arp_xmt ; 
 int /*<<< orphan*/  l_rdesc_arp_xmt ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  send_to_lecd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lec_arp_expire_arp(unsigned long data)
{
	struct lec_arp_table *entry;

	entry = (struct lec_arp_table *)data;

	pr_debug("lec_arp_expire_arp\n");
	if (entry->status == ESI_ARP_PENDING) {
		if (entry->no_tries <= entry->priv->max_retry_count) {
			if (entry->is_rdesc)
				send_to_lecd(entry->priv, l_rdesc_arp_xmt,
					     entry->mac_addr, NULL, NULL);
			else
				send_to_lecd(entry->priv, l_arp_xmt,
					     entry->mac_addr, NULL, NULL);
			entry->no_tries++;
		}
		mod_timer(&entry->timer, jiffies + (1 * HZ));
	}
}