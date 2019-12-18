#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct socket {TYPE_1__* ops; struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/ * sk_destruct; struct pppol2tp_tunnel* sk_user_data; int /*<<< orphan*/  sk_protocol; } ;
struct TYPE_5__ {int /*<<< orphan*/  tunnel_id; } ;
struct pppol2tp_tunnel {scalar_t__ magic; struct sock* sock; int /*<<< orphan*/  list; struct net* pppol2tp_net; int /*<<< orphan*/  hlist_lock; int /*<<< orphan*/ * old_sk_destruct; int /*<<< orphan*/  debug; TYPE_2__ stats; int /*<<< orphan*/ * name; } ;
struct pppol2tp_net {int /*<<< orphan*/  pppol2tp_tunnel_list_lock; int /*<<< orphan*/  pppol2tp_tunnel_list; } ;
struct net {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  encap_rcv; int /*<<< orphan*/  encap_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAFNOSUPPORT ; 
 int EBADF ; 
 int EBUSY ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ L2TP_TUNNEL_MAGIC ; 
 int /*<<< orphan*/  PPPOL2TP_DEFAULT_DEBUG_FLAGS ; 
 int /*<<< orphan*/  PPPOL2TP_MSG_CONTROL ; 
 int /*<<< orphan*/  PRINTK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  UDP_ENCAP_L2TPINUDP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct pppol2tp_tunnel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pppol2tp_net* pppol2tp_pernet (struct net*) ; 
 int /*<<< orphan*/  pppol2tp_tunnel_count ; 
 int /*<<< orphan*/  pppol2tp_tunnel_destruct ; 
 int /*<<< orphan*/  pppol2tp_tunnel_inc_refcount (struct pppol2tp_tunnel*) ; 
 int /*<<< orphan*/  pppol2tp_udp_encap_recv ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* udp_sk (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sock *pppol2tp_prepare_tunnel_socket(struct net *net,
					int fd, u16 tunnel_id, int *error)
{
	int err;
	struct socket *sock = NULL;
	struct sock *sk;
	struct pppol2tp_tunnel *tunnel;
	struct pppol2tp_net *pn;
	struct sock *ret = NULL;

	/* Get the tunnel UDP socket from the fd, which was opened by
	 * the userspace L2TP daemon.
	 */
	err = -EBADF;
	sock = sockfd_lookup(fd, &err);
	if (!sock) {
		PRINTK(-1, PPPOL2TP_MSG_CONTROL, KERN_ERR,
		       "tunl %hu: sockfd_lookup(fd=%d) returned %d\n",
		       tunnel_id, fd, err);
		goto err;
	}

	sk = sock->sk;

	/* Quick sanity checks */
	err = -EPROTONOSUPPORT;
	if (sk->sk_protocol != IPPROTO_UDP) {
		PRINTK(-1, PPPOL2TP_MSG_CONTROL, KERN_ERR,
		       "tunl %hu: fd %d wrong protocol, got %d, expected %d\n",
		       tunnel_id, fd, sk->sk_protocol, IPPROTO_UDP);
		goto err;
	}
	err = -EAFNOSUPPORT;
	if (sock->ops->family != AF_INET) {
		PRINTK(-1, PPPOL2TP_MSG_CONTROL, KERN_ERR,
		       "tunl %hu: fd %d wrong family, got %d, expected %d\n",
		       tunnel_id, fd, sock->ops->family, AF_INET);
		goto err;
	}

	err = -ENOTCONN;

	/* Check if this socket has already been prepped */
	tunnel = (struct pppol2tp_tunnel *)sk->sk_user_data;
	if (tunnel != NULL) {
		/* User-data field already set */
		err = -EBUSY;
		BUG_ON(tunnel->magic != L2TP_TUNNEL_MAGIC);

		/* This socket has already been prepped */
		ret = tunnel->sock;
		goto out;
	}

	/* This socket is available and needs prepping. Create a new tunnel
	 * context and init it.
	 */
	sk->sk_user_data = tunnel = kzalloc(sizeof(struct pppol2tp_tunnel), GFP_KERNEL);
	if (sk->sk_user_data == NULL) {
		err = -ENOMEM;
		goto err;
	}

	tunnel->magic = L2TP_TUNNEL_MAGIC;
	sprintf(&tunnel->name[0], "tunl %hu", tunnel_id);

	tunnel->stats.tunnel_id = tunnel_id;
	tunnel->debug = PPPOL2TP_DEFAULT_DEBUG_FLAGS;

	/* Hook on the tunnel socket destructor so that we can cleanup
	 * if the tunnel socket goes away.
	 */
	tunnel->old_sk_destruct = sk->sk_destruct;
	sk->sk_destruct = &pppol2tp_tunnel_destruct;

	tunnel->sock = sk;
	sk->sk_allocation = GFP_ATOMIC;

	/* Misc init */
	rwlock_init(&tunnel->hlist_lock);

	/* The net we belong to */
	tunnel->pppol2tp_net = net;
	pn = pppol2tp_pernet(net);

	/* Add tunnel to our list */
	INIT_LIST_HEAD(&tunnel->list);
	write_lock_bh(&pn->pppol2tp_tunnel_list_lock);
	list_add(&tunnel->list, &pn->pppol2tp_tunnel_list);
	write_unlock_bh(&pn->pppol2tp_tunnel_list_lock);
	atomic_inc(&pppol2tp_tunnel_count);

	/* Bump the reference count. The tunnel context is deleted
	 * only when this drops to zero.
	 */
	pppol2tp_tunnel_inc_refcount(tunnel);

	/* Mark socket as an encapsulation socket. See net/ipv4/udp.c */
	(udp_sk(sk))->encap_type = UDP_ENCAP_L2TPINUDP;
	(udp_sk(sk))->encap_rcv = pppol2tp_udp_encap_recv;

	ret = tunnel->sock;

	*error = 0;
out:
	if (sock)
		sockfd_put(sock);

	return ret;

err:
	*error = err;
	goto out;
}