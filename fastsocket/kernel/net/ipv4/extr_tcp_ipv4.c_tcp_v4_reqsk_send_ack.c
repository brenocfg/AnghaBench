#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int /*<<< orphan*/  ts_recent; int /*<<< orphan*/  rcv_wnd; } ;
struct TYPE_6__ {scalar_t__ no_srccheck; } ;
struct TYPE_5__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {scalar_t__ rcv_isn; scalar_t__ snt_isn; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_REPLY_ARG_NOSRCCHECK ; 
 TYPE_3__* inet_rsk (struct request_sock*) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 TYPE_1__* tcp_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  tcp_v4_md5_do_lookup (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_v4_send_ack (struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_v4_reqsk_send_ack(struct sock *sk, struct sk_buff *skb,
				  struct request_sock *req)
{
	tcp_v4_send_ack(skb, tcp_rsk(req)->snt_isn + 1,
			tcp_rsk(req)->rcv_isn + 1, req->rcv_wnd,
			req->ts_recent,
			0,
			tcp_v4_md5_do_lookup(sk, ip_hdr(skb)->daddr),
			inet_rsk(req)->no_srccheck ? IP_REPLY_ARG_NOSRCCHECK : 0);
}