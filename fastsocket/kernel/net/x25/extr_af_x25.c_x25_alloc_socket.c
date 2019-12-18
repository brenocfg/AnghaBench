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
struct x25_sock {int /*<<< orphan*/  interrupt_out_queue; int /*<<< orphan*/  interrupt_in_queue; int /*<<< orphan*/  fragment_queue; int /*<<< orphan*/  ack_queue; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_X25 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  x25_proto ; 
 struct x25_sock* x25_sk (struct sock*) ; 

__attribute__((used)) static struct sock *x25_alloc_socket(struct net *net)
{
	struct x25_sock *x25;
	struct sock *sk = sk_alloc(net, AF_X25, GFP_ATOMIC, &x25_proto);

	if (!sk)
		goto out;

	sock_init_data(NULL, sk);

	x25 = x25_sk(sk);
	skb_queue_head_init(&x25->ack_queue);
	skb_queue_head_init(&x25->fragment_queue);
	skb_queue_head_init(&x25->interrupt_in_queue);
	skb_queue_head_init(&x25->interrupt_out_queue);
out:
	return sk;
}