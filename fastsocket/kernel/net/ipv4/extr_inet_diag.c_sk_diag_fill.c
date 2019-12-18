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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct inet_timewait_sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCP_TIME_WAIT ; 
 int inet_csk_diag_fill (struct sock*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*) ; 
 int inet_twsk_diag_fill (struct inet_timewait_sock*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*) ; 

__attribute__((used)) static int sk_diag_fill(struct sock *sk, struct sk_buff *skb,
			int ext, u32 pid, u32 seq, u16 nlmsg_flags,
			const struct nlmsghdr *unlh)
{
	if (sk->sk_state == TCP_TIME_WAIT)
		return inet_twsk_diag_fill((struct inet_timewait_sock *)sk,
					   skb, ext, pid, seq, nlmsg_flags,
					   unlh);
	return inet_csk_diag_fill(sk, skb, ext, pid, seq, nlmsg_flags, unlh);
}