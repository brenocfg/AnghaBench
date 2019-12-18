#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ps_data {int /*<<< orphan*/  bc_buf; int /*<<< orphan*/  num_sta_ps; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  hw_queue; int /*<<< orphan*/  flags; } ;
struct ieee80211_tx_data {TYPE_5__* skb; TYPE_6__* local; TYPE_7__* sdata; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  ieee80211_tx_result ;
struct TYPE_17__ {scalar_t__ type; int /*<<< orphan*/  cab_queue; } ;
struct TYPE_11__ {struct ps_data ps; } ;
struct TYPE_12__ {TYPE_2__ mesh; } ;
struct TYPE_16__ {TYPE_8__ vif; TYPE_3__ u; TYPE_1__* bss; } ;
struct TYPE_13__ {int flags; } ;
struct TYPE_15__ {scalar_t__ total_ps_buffered; TYPE_4__ hw; } ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_10__ {struct ps_data ps; } ;

/* Variables and functions */
 scalar_t__ AP_MAX_BC_BUFFER ; 
 int IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING ; 
 int IEEE80211_HW_QUEUE_CONTROL ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (TYPE_5__*) ; 
 int /*<<< orphan*/  IEEE80211_TX_CTL_SEND_AFTER_DTIM ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 scalar_t__ TOTAL_MAX_TX_BUFFER ; 
 int /*<<< orphan*/  TX_CONTINUE ; 
 int /*<<< orphan*/  TX_QUEUED ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_has_order (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_vif_is_mesh (TYPE_8__*) ; 
 int /*<<< orphan*/  ps_dbg (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  purge_old_ps_buffers (TYPE_6__*) ; 
 int /*<<< orphan*/  skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static ieee80211_tx_result
ieee80211_tx_h_multicast_ps_buf(struct ieee80211_tx_data *tx)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)tx->skb->data;
	struct ps_data *ps;

	/*
	 * broadcast/multicast frame
	 *
	 * If any of the associated/peer stations is in power save mode,
	 * the frame is buffered to be sent after DTIM beacon frame.
	 * This is done either by the hardware or us.
	 */

	/* powersaving STAs currently only in AP/VLAN/mesh mode */
	if (tx->sdata->vif.type == NL80211_IFTYPE_AP ||
	    tx->sdata->vif.type == NL80211_IFTYPE_AP_VLAN) {
		if (!tx->sdata->bss)
			return TX_CONTINUE;

		ps = &tx->sdata->bss->ps;
	} else if (ieee80211_vif_is_mesh(&tx->sdata->vif)) {
		ps = &tx->sdata->u.mesh.ps;
	} else {
		return TX_CONTINUE;
	}


	/* no buffering for ordered frames */
	if (ieee80211_has_order(hdr->frame_control))
		return TX_CONTINUE;

	/* no stations in PS mode */
	if (!atomic_read(&ps->num_sta_ps))
		return TX_CONTINUE;

	info->flags |= IEEE80211_TX_CTL_SEND_AFTER_DTIM;
	if (tx->local->hw.flags & IEEE80211_HW_QUEUE_CONTROL)
		info->hw_queue = tx->sdata->vif.cab_queue;

	/* device releases frame after DTIM beacon */
	if (!(tx->local->hw.flags & IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING))
		return TX_CONTINUE;

	/* buffered in mac80211 */
	if (tx->local->total_ps_buffered >= TOTAL_MAX_TX_BUFFER)
		purge_old_ps_buffers(tx->local);

	if (skb_queue_len(&ps->bc_buf) >= AP_MAX_BC_BUFFER) {
		ps_dbg(tx->sdata,
		       "BC TX buffer full - dropping the oldest frame\n");
		dev_kfree_skb(skb_dequeue(&ps->bc_buf));
	} else
		tx->local->total_ps_buffered++;

	skb_queue_tail(&ps->bc_buf, tx->skb);

	return TX_QUEUED;
}