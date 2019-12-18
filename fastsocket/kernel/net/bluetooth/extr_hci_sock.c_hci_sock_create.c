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
struct sock {int sk_protocol; int /*<<< orphan*/  sk_state; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct socket*) ; 
 int /*<<< orphan*/  BT_OPEN ; 
 int ENOMEM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 scalar_t__ SOCK_RAW ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  bt_sock_link (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  hci_sk_list ; 
 int /*<<< orphan*/  hci_sk_proto ; 
 int /*<<< orphan*/  hci_sock_ops ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hci_sock_create(struct net *net, struct socket *sock, int protocol,
			   int kern)
{
	struct sock *sk;

	BT_DBG("sock %p", sock);

	if (sock->type != SOCK_RAW)
		return -ESOCKTNOSUPPORT;

	sock->ops = &hci_sock_ops;

	sk = sk_alloc(net, PF_BLUETOOTH, GFP_ATOMIC, &hci_sk_proto);
	if (!sk)
		return -ENOMEM;

	sock_init_data(sock, sk);

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = protocol;

	sock->state = SS_UNCONNECTED;
	sk->sk_state = BT_OPEN;

	bt_sock_link(&hci_sk_list, sk);
	return 0;
}