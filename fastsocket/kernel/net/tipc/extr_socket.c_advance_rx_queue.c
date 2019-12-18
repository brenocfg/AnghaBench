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
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_queue_size ; 

__attribute__((used)) static void advance_rx_queue(struct sock *sk)
{
	buf_discard(__skb_dequeue(&sk->sk_receive_queue));
	atomic_dec(&tipc_queue_size);
}