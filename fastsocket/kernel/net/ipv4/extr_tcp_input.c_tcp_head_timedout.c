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
struct tcp_sock {scalar_t__ packets_out; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_skb_timedout (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_write_queue_head (struct sock*) ; 

__attribute__((used)) static inline int tcp_head_timedout(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	return tp->packets_out &&
	       tcp_skb_timedout(sk, tcp_write_queue_head(sk));
}