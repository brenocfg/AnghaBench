#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;
struct sock {size_t sk_family; int sk_userlocks; TYPE_3__* sk_prot; int /*<<< orphan*/ * sk_sleep; int /*<<< orphan*/  sk_refcnt; scalar_t__ sk_priority; scalar_t__ sk_err; int /*<<< orphan*/ * sk_destruct; struct sk_filter* sk_filter; int /*<<< orphan*/  sk_error_queue; int /*<<< orphan*/ * sk_send_head; scalar_t__ sk_forward_alloc; scalar_t__ sk_wmem_queued; int /*<<< orphan*/ * sk_dst_cache; int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_dst_lock; int /*<<< orphan*/  sk_async_wait_queue; int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_omem_alloc; int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_rmem_alloc; TYPE_1__ sk_backlog; int /*<<< orphan*/  sk_node; } ;
struct sk_filter {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_8__ {TYPE_2__ sk_backlog; } ;
struct TYPE_7__ {scalar_t__ sockets_allocated; } ;

/* Variables and functions */
 int SOCK_BINDPORT_LOCK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  SOCK_TIMESTAMP ; 
 int /*<<< orphan*/  SOCK_TIMESTAMPING_RX_SOFTWARE ; 
 scalar_t__ af_callback_keys ; 
 int /*<<< orphan*/ * af_family_clock_key_strings ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class_and_name (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_enable_timestamp () ; 
 int /*<<< orphan*/  percpu_counter_inc (scalar_t__) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* sk_extended (struct sock*) ; 
 int /*<<< orphan*/  sk_filter_charge (struct sock*,struct sk_filter*) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 
 int /*<<< orphan*/  sk_node_init (int /*<<< orphan*/ *) ; 
 struct sock* sk_prot_alloc (TYPE_3__*,int /*<<< orphan*/  const,size_t) ; 
 int /*<<< orphan*/  sk_refcnt_debug_inc (struct sock*) ; 
 int /*<<< orphan*/  sk_set_socket (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  sock_copy (struct sock*,struct sock const*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_lock_init (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_sk_clone_policy (struct sock*) ; 

struct sock *sk_clone(const struct sock *sk, const gfp_t priority)
{
	struct sock *newsk;

	newsk = sk_prot_alloc(sk->sk_prot, priority, sk->sk_family);
	if (newsk != NULL) {
		struct sk_filter *filter;

		sock_copy(newsk, sk);

		/* SANITY */
		get_net(sock_net(newsk));
		sk_node_init(&newsk->sk_node);
		sock_lock_init(newsk);
		bh_lock_sock(newsk);
		newsk->sk_backlog.head	= newsk->sk_backlog.tail = NULL;
		sk_extended(newsk)->sk_backlog.len = 0;

		atomic_set(&newsk->sk_rmem_alloc, 0);
		/*
		 * sk_wmem_alloc set to one (see sk_free() and sock_wfree())
		 */
		atomic_set(&newsk->sk_wmem_alloc, 1);
		atomic_set(&newsk->sk_omem_alloc, 0);
		skb_queue_head_init(&newsk->sk_receive_queue);
		skb_queue_head_init(&newsk->sk_write_queue);
#ifdef CONFIG_NET_DMA
		skb_queue_head_init(&newsk->sk_async_wait_queue);
#endif

		rwlock_init(&newsk->sk_dst_lock);
		rwlock_init(&newsk->sk_callback_lock);
		lockdep_set_class_and_name(&newsk->sk_callback_lock,
				af_callback_keys + newsk->sk_family,
				af_family_clock_key_strings[newsk->sk_family]);

		newsk->sk_dst_cache	= NULL;
		newsk->sk_wmem_queued	= 0;
		newsk->sk_forward_alloc = 0;
		newsk->sk_send_head	= NULL;
		newsk->sk_userlocks	= sk->sk_userlocks & ~SOCK_BINDPORT_LOCK;

		sock_reset_flag(newsk, SOCK_DONE);
		skb_queue_head_init(&newsk->sk_error_queue);

		filter = newsk->sk_filter;
		if (filter != NULL)
			sk_filter_charge(newsk, filter);

		if (unlikely(xfrm_sk_clone_policy(newsk))) {
			/* It is still raw copy of parent, so invalidate
			 * destructor and make plain sk_free() */
			newsk->sk_destruct = NULL;
			sk_free(newsk);
			newsk = NULL;
			goto out;
		}

		newsk->sk_err	   = 0;
		newsk->sk_priority = 0;
		/*
		 * Before updating sk_refcnt, we must commit prior changes to memory
		 * (Documentation/RCU/rculist_nulls.txt for details)
		 */
		smp_wmb();
		atomic_set(&newsk->sk_refcnt, 2);

		/*
		 * Increment the counter in the same struct proto as the master
		 * sock (sk_refcnt_debug_inc uses newsk->sk_prot->socks, that
		 * is the same as sk->sk_prot->socks, as this field was copied
		 * with memcpy).
		 *
		 * This _changes_ the previous behaviour, where
		 * tcp_create_openreq_child always was incrementing the
		 * equivalent to tcp_prot->socks (inet_sock_nr), so this have
		 * to be taken into account in all callers. -acme
		 */
		sk_refcnt_debug_inc(newsk);
		sk_set_socket(newsk, NULL);
		newsk->sk_sleep	 = NULL;

		if (newsk->sk_prot->sockets_allocated)
			percpu_counter_inc(newsk->sk_prot->sockets_allocated);

		if (sock_flag(newsk, SOCK_TIMESTAMP) ||
		    sock_flag(newsk, SOCK_TIMESTAMPING_RX_SOFTWARE))
			net_enable_timestamp();
	}
out:
	return newsk;
}