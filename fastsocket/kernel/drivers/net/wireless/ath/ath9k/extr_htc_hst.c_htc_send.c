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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct htc_target {int dummy; } ;
struct ath9k_htc_tx_ctl {int /*<<< orphan*/  epid; } ;

/* Variables and functions */
 struct ath9k_htc_tx_ctl* HTC_SKB_CB (struct sk_buff*) ; 
 int htc_issue_send (struct htc_target*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int htc_send(struct htc_target *target, struct sk_buff *skb)
{
	struct ath9k_htc_tx_ctl *tx_ctl;

	tx_ctl = HTC_SKB_CB(skb);
	return htc_issue_send(target, skb, skb->len, 0, tx_ctl->epid);
}