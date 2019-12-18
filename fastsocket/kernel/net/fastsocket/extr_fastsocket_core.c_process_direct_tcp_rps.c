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
struct tcphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_rcv_dst; } ;
struct sk_buff {scalar_t__ sock_dst; struct sock* peek_sk; TYPE_1__* dev; scalar_t__ data; } ;
struct iphdr {int ihl; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DIRECT_TCP ; 
 scalar_t__ TCP_TIME_WAIT ; 
 struct sock* __inet_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 scalar_t__ likely (struct sock*) ; 
 scalar_t__ pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,scalar_t__) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 

__attribute__((used)) static int process_direct_tcp_rps(struct sk_buff *skb)
{
	struct iphdr *iph = (struct iphdr *)skb->data;
	int iphl = iph->ihl;

	if (pskb_may_pull(skb, (iphl * 4) + sizeof(struct tcphdr))) {
		struct sock *sk;
		struct tcphdr *th = (struct tcphdr *)(skb->data + (iphl * 4));

		if (!skb->peek_sk) {
			sk = __inet_lookup(&init_net, &tcp_hashinfo, iph->saddr, th->source, iph->daddr, th->dest, skb->dev->ifindex);;
			skb->peek_sk = sk;
		} else
			sk = skb->peek_sk;

		if (likely(sk)) {
			if ((sk->sk_state != TCP_TIME_WAIT) && sock_flag(sk, SOCK_DIRECT_TCP)) {
				//DPRINTK(DEBUG, "Skb 0x%p[:%u] hit DIRECT_TCP socket 0x%p[:%u]\n", skb, ntohs(th->dest), sk, inet_sk(sk)->num);
				if(sk->sk_rcv_dst) {
					skb_dst_set(skb, sk->sk_rcv_dst);
					skb->sock_dst = sk->sk_rcv_dst;
					//DPRINTK(DEBUG, "Direct TCP socket 0x%p has dst record 0x%p[%u]\n", sk, sk->sk_rcv_dst, atomic_read(&sk->sk_rcv_dst->__refcnt));a
				}
				//} else {
				//	DPRINTK(DEBUG, "Direct TCP socket 0x%p has not dst record\n", sk);
				//}

			//} else {
			//	if (ntohs(th->dest) != 22)
			//		DPRINTK(DEBUG, "Skb 0x%p[:%u] hit common socket 0x%p[:%u]\n", skb,ntohs(th->dest), sk, inet_sk(sk)->num);
			}
		}
	}

	return -1;
}