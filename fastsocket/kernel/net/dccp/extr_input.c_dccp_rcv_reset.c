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
typedef  scalar_t__ u8 ;
struct sock {scalar_t__ sk_err; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccph_reset_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_TIME_WAIT ; 
 int /*<<< orphan*/  POLL_ERR ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_WAKE_IO ; 
 int /*<<< orphan*/  dccp_fin (struct sock*,struct sk_buff*) ; 
 TYPE_1__* dccp_hdr_reset (struct sk_buff*) ; 
 scalar_t__ dccp_reset_code_convert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_time_wait (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dccp_rcv_reset(struct sock *sk, struct sk_buff *skb)
{
	u8 err = dccp_reset_code_convert(dccp_hdr_reset(skb)->dccph_reset_code);

	sk->sk_err = err;

	/* Queue the equivalent of TCP fin so that dccp_recvmsg exits the loop */
	dccp_fin(sk, skb);

	if (err && !sock_flag(sk, SOCK_DEAD))
		sk_wake_async(sk, SOCK_WAKE_IO, POLL_ERR);
	dccp_time_wait(sk, DCCP_TIME_WAIT, 0);
}