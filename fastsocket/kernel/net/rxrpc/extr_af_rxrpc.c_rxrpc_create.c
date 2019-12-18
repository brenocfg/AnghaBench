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
struct socket {scalar_t__ type; int /*<<< orphan*/  state; int /*<<< orphan*/ * ops; } ;
struct sock {int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_max_ack_backlog; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state; } ;
struct rxrpc_sock {int proto; int /*<<< orphan*/  srx; int /*<<< orphan*/  call_lock; int /*<<< orphan*/  acceptq; int /*<<< orphan*/  secureq; int /*<<< orphan*/  listen_link; int /*<<< orphan*/  calls; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PF_INET ; 
 int /*<<< orphan*/  PF_RXRPC ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  RXRPC_UNCONNECTED ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  _enter (char*,struct socket*,int) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_sock*) ; 
 struct net init_net ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_proto ; 
 int /*<<< orphan*/  rxrpc_rpc_ops ; 
 struct rxrpc_sock* rxrpc_sk (struct sock*) ; 
 int /*<<< orphan*/  rxrpc_sock_destructor ; 
 int /*<<< orphan*/  rxrpc_write_space ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sysctl_rxrpc_max_qlen ; 

__attribute__((used)) static int rxrpc_create(struct net *net, struct socket *sock, int protocol,
			int kern)
{
	struct rxrpc_sock *rx;
	struct sock *sk;

	_enter("%p,%d", sock, protocol);

	if (net != &init_net)
		return -EAFNOSUPPORT;

	/* we support transport protocol UDP only */
	if (protocol != PF_INET)
		return -EPROTONOSUPPORT;

	if (sock->type != SOCK_DGRAM)
		return -ESOCKTNOSUPPORT;

	sock->ops = &rxrpc_rpc_ops;
	sock->state = SS_UNCONNECTED;

	sk = sk_alloc(net, PF_RXRPC, GFP_KERNEL, &rxrpc_proto);
	if (!sk)
		return -ENOMEM;

	sock_init_data(sock, sk);
	sk->sk_state		= RXRPC_UNCONNECTED;
	sk->sk_write_space	= rxrpc_write_space;
	sk->sk_max_ack_backlog	= sysctl_rxrpc_max_qlen;
	sk->sk_destruct		= rxrpc_sock_destructor;

	rx = rxrpc_sk(sk);
	rx->proto = protocol;
	rx->calls = RB_ROOT;

	INIT_LIST_HEAD(&rx->listen_link);
	INIT_LIST_HEAD(&rx->secureq);
	INIT_LIST_HEAD(&rx->acceptq);
	rwlock_init(&rx->call_lock);
	memset(&rx->srx, 0, sizeof(rx->srx));

	_leave(" = 0 [%p]", rx);
	return 0;
}