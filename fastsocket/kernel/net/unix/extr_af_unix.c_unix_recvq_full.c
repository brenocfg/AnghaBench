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
struct sock {scalar_t__ sk_max_ack_backlog; int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int unix_recvq_full(struct sock const *sk)
{
	return skb_queue_len(&sk->sk_receive_queue) > sk->sk_max_ack_backlog;
}