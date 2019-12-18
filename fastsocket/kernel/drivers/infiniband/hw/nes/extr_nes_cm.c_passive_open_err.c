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
struct sk_buff {int dummy; } ;
struct nes_cm_node {int /*<<< orphan*/  cm_core; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_CM_STATE_CLOSED ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  cleanup_retrans_entry (struct nes_cm_node*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,struct nes_cm_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rem_ref_cm_node (int /*<<< orphan*/ ,struct nes_cm_node*) ; 
 int /*<<< orphan*/  send_reset (struct nes_cm_node*,struct sk_buff*) ; 

__attribute__((used)) static void passive_open_err(struct nes_cm_node *cm_node, struct sk_buff *skb,
			     int reset)
{
	cleanup_retrans_entry(cm_node);
	cm_node->state = NES_CM_STATE_CLOSED;
	if (reset) {
		nes_debug(NES_DBG_CM, "passive_open_err sending RST for "
			  "cm_node=%p state =%d\n", cm_node, cm_node->state);
		send_reset(cm_node, skb);
	} else {
		dev_kfree_skb_any(skb);
		rem_ref_cm_node(cm_node->cm_core, cm_node);
	}
}