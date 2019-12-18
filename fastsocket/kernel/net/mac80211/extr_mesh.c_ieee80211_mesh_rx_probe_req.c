#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct ieee802_11_elems {scalar_t__ ssid_len; scalar_t__ mesh_id_len; int /*<<< orphan*/  mesh_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_if_mesh {scalar_t__ mesh_id_len; int /*<<< orphan*/  beacon; int /*<<< orphan*/  mesh_id; } ;
struct TYPE_6__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {TYPE_4__ vif; TYPE_1__ u; struct ieee80211_local* local; } ;
struct TYPE_7__ {int /*<<< orphan*/ * variable; } ;
struct TYPE_8__ {TYPE_2__ probe_req; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  sa; int /*<<< orphan*/  da; int /*<<< orphan*/  frame_control; TYPE_3__ u; } ;
struct ieee80211_local {scalar_t__ tx_headroom; } ;
struct beacon_data {scalar_t__ tail_len; int /*<<< orphan*/  tail; scalar_t__ head_len; int /*<<< orphan*/  head; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int IEEE80211_FTYPE_MGMT ; 
 TYPE_5__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_STYPE_PROBE_RESP ; 
 int /*<<< orphan*/  IEEE80211_TX_INTFL_DONT_ENCRYPT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee802_11_parse_elems (int /*<<< orphan*/ *,size_t,int,struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct beacon_data* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void
ieee80211_mesh_rx_probe_req(struct ieee80211_sub_if_data *sdata,
			    struct ieee80211_mgmt *mgmt, size_t len)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	struct sk_buff *presp;
	struct beacon_data *bcn;
	struct ieee80211_mgmt *hdr;
	struct ieee802_11_elems elems;
	size_t baselen;
	u8 *pos;

	pos = mgmt->u.probe_req.variable;
	baselen = (u8 *) pos - (u8 *) mgmt;
	if (baselen > len)
		return;

	ieee802_11_parse_elems(pos, len - baselen, false, &elems);

	/* 802.11-2012 10.1.4.3.2 */
	if ((!ether_addr_equal(mgmt->da, sdata->vif.addr) &&
	     !is_broadcast_ether_addr(mgmt->da)) ||
	    elems.ssid_len != 0)
		return;

	if (elems.mesh_id_len != 0 &&
	    (elems.mesh_id_len != ifmsh->mesh_id_len ||
	     memcmp(elems.mesh_id, ifmsh->mesh_id, ifmsh->mesh_id_len)))
		return;

	rcu_read_lock();
	bcn = rcu_dereference(ifmsh->beacon);

	if (!bcn)
		goto out;

	presp = dev_alloc_skb(local->tx_headroom +
			      bcn->head_len + bcn->tail_len);
	if (!presp)
		goto out;

	skb_reserve(presp, local->tx_headroom);
	memcpy(skb_put(presp, bcn->head_len), bcn->head, bcn->head_len);
	memcpy(skb_put(presp, bcn->tail_len), bcn->tail, bcn->tail_len);
	hdr = (struct ieee80211_mgmt *) presp->data;
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					 IEEE80211_STYPE_PROBE_RESP);
	memcpy(hdr->da, mgmt->sa, ETH_ALEN);
	IEEE80211_SKB_CB(presp)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;
	ieee80211_tx_skb(sdata, presp);
out:
	rcu_read_unlock();
}