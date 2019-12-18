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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct pppol2tp_tunnel {int /*<<< orphan*/  name; int /*<<< orphan*/  debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PPPOL2TP_MSG_DATA ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pppol2tp_recv_core (struct sock*,struct sk_buff*) ; 
 struct pppol2tp_tunnel* pppol2tp_sock_to_tunnel (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static int pppol2tp_udp_encap_recv(struct sock *sk, struct sk_buff *skb)
{
	struct pppol2tp_tunnel *tunnel;

	tunnel = pppol2tp_sock_to_tunnel(sk);
	if (tunnel == NULL)
		goto pass_up;

	PRINTK(tunnel->debug, PPPOL2TP_MSG_DATA, KERN_DEBUG,
	       "%s: received %d bytes\n", tunnel->name, skb->len);

	if (pppol2tp_recv_core(sk, skb))
		goto pass_up_put;

	sock_put(sk);
	return 0;

pass_up_put:
	sock_put(sk);
pass_up:
	return 1;
}