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
struct sock {int /*<<< orphan*/  sk_shutdown; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  dccp_enqueue_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dccp_fin(struct sock *sk, struct sk_buff *skb)
{
	/*
	 * On receiving Close/CloseReq, both RD/WR shutdown are performed.
	 * RFC 4340, 8.3 says that we MAY send further Data/DataAcks after
	 * receiving the closing segment, but there is no guarantee that such
	 * data will be processed at all.
	 */
	sk->sk_shutdown = SHUTDOWN_MASK;
	sock_set_flag(sk, SOCK_DONE);
	dccp_enqueue_skb(sk, skb);
}