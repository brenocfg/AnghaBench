#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ tx_seq; int sar; } ;
struct TYPE_3__ {int buffer_seq_srej; } ;

/* Variables and functions */
 int L2CAP_CTRL_SAR_SHIFT ; 
 int /*<<< orphan*/  SREJ_QUEUE (struct sock*) ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sar_reassembly_sdu (struct sock*,struct sk_buff*,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_check_srej_gap(struct sock *sk, u8 tx_seq)
{
	struct sk_buff *skb;
	u16 control = 0;

	while((skb = skb_peek(SREJ_QUEUE(sk)))) {
		if (bt_cb(skb)->tx_seq != tx_seq)
			break;

		skb = skb_dequeue(SREJ_QUEUE(sk));
		control |= bt_cb(skb)->sar << L2CAP_CTRL_SAR_SHIFT;
		l2cap_sar_reassembly_sdu(sk, skb, control);
		l2cap_pi(sk)->buffer_seq_srej =
			(l2cap_pi(sk)->buffer_seq_srej + 1) % 64;
		tx_seq++;
	}
}