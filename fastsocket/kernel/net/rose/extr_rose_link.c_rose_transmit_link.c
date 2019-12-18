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
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  dev; } ;
struct rose_neigh {scalar_t__ dce_mode; int /*<<< orphan*/  queue; scalar_t__ restarted; scalar_t__ loopback; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_P_ROSE ; 
 scalar_t__ FW_ACCEPT ; 
 int /*<<< orphan*/  PF_ROSE ; 
 scalar_t__ call_fw_firewall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff**) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rose_link_up (struct rose_neigh*) ; 
 int /*<<< orphan*/  rose_loopback_queue (struct sk_buff*,struct rose_neigh*) ; 
 int /*<<< orphan*/  rose_send_frame (struct sk_buff*,struct rose_neigh*) ; 
 int /*<<< orphan*/  rose_start_t0timer (struct rose_neigh*) ; 
 int /*<<< orphan*/  rose_t0timer_running (struct rose_neigh*) ; 
 int /*<<< orphan*/  rose_transmit_restart_request (struct rose_neigh*) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void rose_transmit_link(struct sk_buff *skb, struct rose_neigh *neigh)
{
	unsigned char *dptr;

#if 0
	if (call_fw_firewall(PF_ROSE, skb->dev, skb->data, NULL, &skb) != FW_ACCEPT) {
		kfree_skb(skb);
		return;
	}
#endif

	if (neigh->loopback) {
		rose_loopback_queue(skb, neigh);
		return;
	}

	if (!rose_link_up(neigh))
		neigh->restarted = 0;

	dptr = skb_push(skb, 1);
	*dptr++ = AX25_P_ROSE;

	if (neigh->restarted) {
		if (!rose_send_frame(skb, neigh))
			kfree_skb(skb);
	} else {
		skb_queue_tail(&neigh->queue, skb);

		if (!rose_t0timer_running(neigh)) {
			rose_transmit_restart_request(neigh);
			neigh->dce_mode = 0;
			rose_start_t0timer(neigh);
		}
	}
}