#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int type; int /*<<< orphan*/ * ops; } ;
struct sock {int sk_protocol; int /*<<< orphan*/  sk_destruct; TYPE_1__* sk_protinfo; } ;
struct net {int dummy; } ;
struct TYPE_3__ {struct sock* sk; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
#define  AX25_P_ARP 136 
#define  AX25_P_IP 135 
#define  AX25_P_NETROM 134 
#define  AX25_P_ROSE 133 
#define  AX25_P_SEGMENT 132 
 int AX25_P_TEXT ; 
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  PF_AX25 131 
#define  SOCK_DGRAM 130 
#define  SOCK_RAW 129 
#define  SOCK_SEQPACKET 128 
 TYPE_1__* ax25_create_cb () ; 
 int /*<<< orphan*/  ax25_free_sock ; 
 int /*<<< orphan*/  ax25_proto ; 
 int /*<<< orphan*/  ax25_proto_ops ; 
 int /*<<< orphan*/  ax25_protocol_is_registered (int const) ; 
 struct net init_net ; 
 struct sock* sk_alloc (struct net*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 

__attribute__((used)) static int ax25_create(struct net *net, struct socket *sock, int protocol,
		       int kern)
{
	struct sock *sk;
	ax25_cb *ax25;

	if (net != &init_net)
		return -EAFNOSUPPORT;

	switch (sock->type) {
	case SOCK_DGRAM:
		if (protocol == 0 || protocol == PF_AX25)
			protocol = AX25_P_TEXT;
		break;

	case SOCK_SEQPACKET:
		switch (protocol) {
		case 0:
		case PF_AX25:	/* For CLX */
			protocol = AX25_P_TEXT;
			break;
		case AX25_P_SEGMENT:
#ifdef CONFIG_INET
		case AX25_P_ARP:
		case AX25_P_IP:
#endif
#ifdef CONFIG_NETROM
		case AX25_P_NETROM:
#endif
#ifdef CONFIG_ROSE
		case AX25_P_ROSE:
#endif
			return -ESOCKTNOSUPPORT;
#ifdef CONFIG_NETROM_MODULE
		case AX25_P_NETROM:
			if (ax25_protocol_is_registered(AX25_P_NETROM))
				return -ESOCKTNOSUPPORT;
#endif
#ifdef CONFIG_ROSE_MODULE
		case AX25_P_ROSE:
			if (ax25_protocol_is_registered(AX25_P_ROSE))
				return -ESOCKTNOSUPPORT;
#endif
		default:
			break;
		}
		break;

	case SOCK_RAW:
		break;
	default:
		return -ESOCKTNOSUPPORT;
	}

	sk = sk_alloc(net, PF_AX25, GFP_ATOMIC, &ax25_proto);
	if (sk == NULL)
		return -ENOMEM;

	ax25 = sk->sk_protinfo = ax25_create_cb();
	if (!ax25) {
		sk_free(sk);
		return -ENOMEM;
	}

	sock_init_data(sock, sk);

	sk->sk_destruct = ax25_free_sock;
	sock->ops    = &ax25_proto_ops;
	sk->sk_protocol = protocol;

	ax25->sk    = sk;

	return 0;
}