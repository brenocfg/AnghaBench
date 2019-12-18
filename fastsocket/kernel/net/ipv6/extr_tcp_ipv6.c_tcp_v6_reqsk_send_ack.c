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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int /*<<< orphan*/  ts_recent; int /*<<< orphan*/  rcv_wnd; } ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_3__ {scalar_t__ rcv_isn; scalar_t__ snt_isn; } ;

/* Variables and functions */
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 TYPE_1__* tcp_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  tcp_v6_md5_do_lookup (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_v6_send_ack (struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_v6_reqsk_send_ack(struct sock *sk, struct sk_buff *skb,
				  struct request_sock *req)
{
	tcp_v6_send_ack(skb, tcp_rsk(req)->snt_isn + 1, tcp_rsk(req)->rcv_isn + 1, req->rcv_wnd, req->ts_recent,
			tcp_v6_md5_do_lookup(sk, &ipv6_hdr(skb)->daddr));
}