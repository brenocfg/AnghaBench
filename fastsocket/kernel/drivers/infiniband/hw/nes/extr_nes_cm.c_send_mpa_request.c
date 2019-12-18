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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nes_cm_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPA_KEY_REQUEST ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  NES_TIMER_TYPE_SEND ; 
 int /*<<< orphan*/  SET_ACK ; 
 int /*<<< orphan*/  cm_build_mpa_frame (struct nes_cm_node*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  form_cm_frame (struct sk_buff*,struct nes_cm_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*) ; 
 int schedule_nes_timer (struct nes_cm_node*,struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_mpa_request(struct nes_cm_node *cm_node, struct sk_buff *skb)
{
	u8 start_addr = 0;
	u8 *start_ptr = &start_addr;
	u8 **start_buff = &start_ptr;
	u16 buff_len = 0;

	if (!skb) {
		nes_debug(NES_DBG_CM, "skb set to NULL\n");
		return -1;
	}

	/* send an MPA Request frame */
	cm_build_mpa_frame(cm_node, start_buff, &buff_len, NULL, MPA_KEY_REQUEST);
	form_cm_frame(skb, cm_node, NULL, 0, *start_buff, buff_len, SET_ACK);

	return schedule_nes_timer(cm_node, skb, NES_TIMER_TYPE_SEND, 1, 0);
}