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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct inet_sock {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_csum_outgoing (struct sk_buff*) ; 
 struct dccp_hdr* dccp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_v4_csum_finish (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 

void dccp_v4_send_check(struct sock *sk, int unused, struct sk_buff *skb)
{
	const struct inet_sock *inet = inet_sk(sk);
	struct dccp_hdr *dh = dccp_hdr(skb);

	dccp_csum_outgoing(skb);
	dh->dccph_checksum = dccp_v4_csum_finish(skb, inet->saddr, inet->daddr);
}