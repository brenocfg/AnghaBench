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
struct net_lro_mgr {int features; } ;
struct net_lro_desc {int pkt_aggr_cnt; int /*<<< orphan*/  parent; int /*<<< orphan*/  vlan_tag; scalar_t__ vgrp; int /*<<< orphan*/  mss; } ;
struct TYPE_2__ {int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 int LRO_F_NAPI ; 
 int /*<<< orphan*/  LRO_INC_STATS (struct net_lro_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushed ; 
 int /*<<< orphan*/  lro_clear_desc (struct net_lro_desc*) ; 
 int /*<<< orphan*/  lro_update_tcp_ip_header (struct net_lro_desc*) ; 
 int /*<<< orphan*/  netif_receive_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_hwaccel_receive_skb (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_hwaccel_rx (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lro_flush(struct net_lro_mgr *lro_mgr,
		      struct net_lro_desc *lro_desc)
{
	if (lro_desc->pkt_aggr_cnt > 1)
		lro_update_tcp_ip_header(lro_desc);

	skb_shinfo(lro_desc->parent)->gso_size = lro_desc->mss;

	if (lro_desc->vgrp) {
		if (lro_mgr->features & LRO_F_NAPI)
			vlan_hwaccel_receive_skb(lro_desc->parent,
						 lro_desc->vgrp,
						 lro_desc->vlan_tag);
		else
			vlan_hwaccel_rx(lro_desc->parent,
					lro_desc->vgrp,
					lro_desc->vlan_tag);

	} else {
		if (lro_mgr->features & LRO_F_NAPI)
			netif_receive_skb(lro_desc->parent);
		else
			netif_rx(lro_desc->parent);
	}

	LRO_INC_STATS(lro_mgr, flushed);
	lro_clear_desc(lro_desc);
}