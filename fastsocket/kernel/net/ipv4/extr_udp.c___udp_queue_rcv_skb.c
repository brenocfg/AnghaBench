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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  rxhash; } ;
struct TYPE_2__ {scalar_t__ daddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IS_UDPLITE (struct sock*) ; 
 int /*<<< orphan*/  UDP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UDP_MIB_INERRORS ; 
 int /*<<< orphan*/  UDP_MIB_RCVBUFERRORS ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_rps_save_rxhash (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_udp_fail_queue_rcv_skb (int,struct sock*) ; 

__attribute__((used)) static int __udp_queue_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
	int rc;

	if (inet_sk(sk)->daddr)
		sock_rps_save_rxhash(sk, skb->rxhash);

	rc = sock_queue_rcv_skb(sk, skb);
	if (rc < 0) {
		int is_udplite = IS_UDPLITE(sk);

		/* Note that an ENOMEM error is charged twice */
		if (rc == -ENOMEM)
			UDP_INC_STATS_BH(sock_net(sk), UDP_MIB_RCVBUFERRORS,
					is_udplite);
		UDP_INC_STATS_BH(sock_net(sk), UDP_MIB_INERRORS, is_udplite);
		kfree_skb(skb);
		trace_udp_fail_queue_rcv_skb(rc, sk);
		return -1;
	}

	return 0;
}