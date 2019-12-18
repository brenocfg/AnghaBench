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
struct sock {int /*<<< orphan*/  (* sk_destruct ) (struct sock*) ;struct pppol2tp_tunnel* sk_user_data; } ;
struct pppol2tp_tunnel {int /*<<< orphan*/  (* old_sk_destruct ) (struct sock*) ;int /*<<< orphan*/ * sock; int /*<<< orphan*/  name; int /*<<< orphan*/  debug; } ;
struct TYPE_2__ {int /*<<< orphan*/ * encap_rcv; scalar_t__ encap_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PPPOL2TP_MSG_CONTROL ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pppol2tp_tunnel_closeall (struct pppol2tp_tunnel*) ; 
 int /*<<< orphan*/  pppol2tp_tunnel_dec_refcount (struct pppol2tp_tunnel*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 TYPE_1__* udp_sk (struct sock*) ; 

__attribute__((used)) static void pppol2tp_tunnel_destruct(struct sock *sk)
{
	struct pppol2tp_tunnel *tunnel;

	tunnel = sk->sk_user_data;
	if (tunnel == NULL)
		goto end;

	PRINTK(tunnel->debug, PPPOL2TP_MSG_CONTROL, KERN_INFO,
	       "%s: closing...\n", tunnel->name);

	/* Close all sessions */
	pppol2tp_tunnel_closeall(tunnel);

	/* No longer an encapsulation socket. See net/ipv4/udp.c */
	(udp_sk(sk))->encap_type = 0;
	(udp_sk(sk))->encap_rcv = NULL;

	/* Remove hooks into tunnel socket */
	tunnel->sock = NULL;
	sk->sk_destruct = tunnel->old_sk_destruct;
	sk->sk_user_data = NULL;

	/* Call original (UDP) socket descructor */
	if (sk->sk_destruct != NULL)
		(*sk->sk_destruct)(sk);

	pppol2tp_tunnel_dec_refcount(tunnel);

end:
	return;
}