#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct unix_sock {int /*<<< orphan*/  peer_wait; int /*<<< orphan*/  readlock; int /*<<< orphan*/  link; int /*<<< orphan*/  inflight; int /*<<< orphan*/  lock; int /*<<< orphan*/ * mnt; int /*<<< orphan*/ * dentry; } ;
struct socket {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct sock {int /*<<< orphan*/  sk_prot; int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_max_ack_backlog; int /*<<< orphan*/  sk_write_space; TYPE_1__ sk_receive_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  sysctl_max_dgram_qlen; } ;
struct net {TYPE_2__ unx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  af_unix_sk_receive_queue_lock_key ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_max_files () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_insert_socket (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  unix_nr_socks ; 
 int /*<<< orphan*/  unix_proto ; 
 struct unix_sock* unix_sk (struct sock*) ; 
 int /*<<< orphan*/  unix_sock_destructor ; 
 int /*<<< orphan*/  unix_sockets_unbound ; 
 int /*<<< orphan*/  unix_write_space ; 

__attribute__((used)) static struct sock *unix_create1(struct net *net, struct socket *sock)
{
	struct sock *sk = NULL;
	struct unix_sock *u;

	atomic_long_inc(&unix_nr_socks);
	if (atomic_long_read(&unix_nr_socks) > 2 * get_max_files())
		goto out;

	sk = sk_alloc(net, PF_UNIX, GFP_KERNEL, &unix_proto);
	if (!sk)
		goto out;

	sock_init_data(sock, sk);
	lockdep_set_class(&sk->sk_receive_queue.lock,
				&af_unix_sk_receive_queue_lock_key);

	sk->sk_write_space	= unix_write_space;
	sk->sk_max_ack_backlog	= net->unx.sysctl_max_dgram_qlen;
	sk->sk_destruct		= unix_sock_destructor;
	u	  = unix_sk(sk);
	u->dentry = NULL;
	u->mnt	  = NULL;
	spin_lock_init(&u->lock);
	atomic_long_set(&u->inflight, 0);
	INIT_LIST_HEAD(&u->link);
	mutex_init(&u->readlock); /* single task reading lock */
	init_waitqueue_head(&u->peer_wait);
	unix_insert_socket(unix_sockets_unbound, sk);
out:
	if (sk == NULL)
		atomic_long_dec(&unix_nr_socks);
	else {
		local_bh_disable();
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
		local_bh_enable();
	}
	return sk;
}