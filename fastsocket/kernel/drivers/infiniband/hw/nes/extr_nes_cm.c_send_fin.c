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
struct nes_cm_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_CM_BUFFER ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  NES_TIMER_TYPE_SEND ; 
 int SET_ACK ; 
 int SET_FIN ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  form_cm_frame (struct sk_buff*,struct nes_cm_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*) ; 
 int schedule_nes_timer (struct nes_cm_node*,struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_fin(struct nes_cm_node *cm_node, struct sk_buff *skb)
{
	int ret;

	/* if we didn't get a frame get one */
	if (!skb)
		skb = dev_alloc_skb(MAX_CM_BUFFER);

	if (!skb) {
		nes_debug(NES_DBG_CM, "Failed to get a Free pkt\n");
		return -1;
	}

	form_cm_frame(skb, cm_node, NULL, 0, NULL, 0, SET_ACK | SET_FIN);
	ret = schedule_nes_timer(cm_node, skb, NES_TIMER_TYPE_SEND, 1, 0);

	return ret;
}