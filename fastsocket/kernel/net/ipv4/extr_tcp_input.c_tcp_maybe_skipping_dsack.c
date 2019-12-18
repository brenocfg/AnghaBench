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
struct tcp_sacktag_state {int dummy; } ;
struct tcp_sack_block {int /*<<< orphan*/  end_seq; int /*<<< orphan*/  start_seq; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* tcp_sacktag_skip (struct sk_buff*,struct sock*,struct tcp_sacktag_state*,int /*<<< orphan*/ ) ; 
 struct sk_buff* tcp_sacktag_walk (struct sk_buff*,struct sock*,int /*<<< orphan*/ *,struct tcp_sacktag_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct sk_buff *tcp_maybe_skipping_dsack(struct sk_buff *skb,
						struct sock *sk,
						struct tcp_sack_block *next_dup,
						struct tcp_sacktag_state *state,
						u32 skip_to_seq)
{
	if (next_dup == NULL)
		return skb;

	if (before(next_dup->start_seq, skip_to_seq)) {
		skb = tcp_sacktag_skip(skb, sk, state, next_dup->start_seq);
		skb = tcp_sacktag_walk(skb, sk, NULL, state,
				       next_dup->start_seq, next_dup->end_seq,
				       1);
	}

	return skb;
}