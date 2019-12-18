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
struct sk_buff {scalar_t__ dropcount; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_RXQ_OVFL ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RXQ_OVFL ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

inline void sock_recv_drops(struct msghdr *msg, struct sock *sk, struct sk_buff *skb)
{
	if (sock_flag(sk, SOCK_RXQ_OVFL) && skb && skb->dropcount)
		put_cmsg(msg, SOL_SOCKET, SO_RXQ_OVFL,
			sizeof(__u32), &skb->dropcount);
}