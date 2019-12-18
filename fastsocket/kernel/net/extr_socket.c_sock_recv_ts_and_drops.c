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
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sock_recv_drops (struct msghdr*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_recv_timestamp (struct msghdr*,struct sock*,struct sk_buff*) ; 

void sock_recv_ts_and_drops(struct msghdr *msg, struct sock *sk,
	struct sk_buff *skb)
{
	sock_recv_timestamp(msg, sk, skb);
	sock_recv_drops(msg, sk, skb);
}