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
struct udp_sock {scalar_t__ pending; scalar_t__ len; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct flowi {int /*<<< orphan*/  fl_ip_dport; int /*<<< orphan*/  fl4_dst; } ;
struct TYPE_2__ {struct flowi fl; } ;
struct inet_sock {TYPE_1__ cork; } ;

/* Variables and functions */
 struct inet_sock* inet_sk (struct sock*) ; 
 struct sk_buff* ip_finish_skb (struct sock*) ; 
 int udp_send_skb (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct udp_sock* udp_sk (struct sock*) ; 

int udp_push_pending_frames(struct sock *sk)
{
	struct udp_sock  *up = udp_sk(sk);
	struct inet_sock *inet = inet_sk(sk);
	struct flowi *fl = &inet->cork.fl;
	struct sk_buff *skb;
	int err = 0;

	skb = ip_finish_skb(sk);
	if (!skb)
		goto out;

	err = udp_send_skb(skb, fl->fl4_dst, fl->fl_ip_dport);

out:
	up->len = 0;
	up->pending = 0;
	return err;
}