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
struct socket {struct sock* sk; int /*<<< orphan*/  wait; int /*<<< orphan*/  type; } ;
struct sock {size_t sk_family; int sk_rcvlowat; int /*<<< orphan*/  sk_drops; int /*<<< orphan*/  sk_refcnt; int /*<<< orphan*/  sk_stamp; void* sk_sndtimeo; void* sk_rcvtimeo; scalar_t__ sk_write_pending; scalar_t__ sk_sndmsg_off; int /*<<< orphan*/ * sk_sndmsg_page; int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_dst_lock; int /*<<< orphan*/ * sk_sleep; int /*<<< orphan*/  sk_type; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/  sk_timer; int /*<<< orphan*/ * sk_send_head; int /*<<< orphan*/  sk_async_wait_queue; int /*<<< orphan*/  sk_error_queue; int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sk_peer_cred; int /*<<< orphan*/ * sk_peer_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 scalar_t__ af_callback_keys ; 
 int /*<<< orphan*/ * af_family_clock_key_strings ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_set (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class_and_name (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* sk_extended (struct sock*) ; 
 int /*<<< orphan*/  sk_set_socket (struct sock*,struct socket*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  sock_def_destruct ; 
 int /*<<< orphan*/  sock_def_error_report ; 
 int /*<<< orphan*/  sock_def_readable ; 
 int /*<<< orphan*/  sock_def_wakeup ; 
 int /*<<< orphan*/  sock_def_write_space ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_rmem_default ; 
 int /*<<< orphan*/  sysctl_wmem_default ; 

void sock_init_data(struct socket *sock, struct sock *sk)
{
	skb_queue_head_init(&sk->sk_receive_queue);
	skb_queue_head_init(&sk->sk_write_queue);
	skb_queue_head_init(&sk->sk_error_queue);
#ifdef CONFIG_NET_DMA
	skb_queue_head_init(&sk->sk_async_wait_queue);
#endif

	sk->sk_send_head	=	NULL;

	init_timer(&sk->sk_timer);

	sk->sk_allocation	=	GFP_KERNEL;
	sk->sk_rcvbuf		=	sysctl_rmem_default;
	sk->sk_sndbuf		=	sysctl_wmem_default;
	sk->sk_state		=	TCP_CLOSE;
	sk_set_socket(sk, sock);

	sock_set_flag(sk, SOCK_ZAPPED);

	if (sock) {
		sk->sk_type	=	sock->type;
		sk->sk_sleep	=	&sock->wait;
		sock->sk	=	sk;
	} else
		sk->sk_sleep	=	NULL;

	rwlock_init(&sk->sk_dst_lock);
	rwlock_init(&sk->sk_callback_lock);
	lockdep_set_class_and_name(&sk->sk_callback_lock,
			af_callback_keys + sk->sk_family,
			af_family_clock_key_strings[sk->sk_family]);

	sk->sk_state_change	=	sock_def_wakeup;
	sk->sk_data_ready	=	sock_def_readable;
	sk->sk_write_space	=	sock_def_write_space;
	sk->sk_error_report	=	sock_def_error_report;
	sk->sk_destruct		=	sock_def_destruct;

	sk->sk_sndmsg_page	=	NULL;
	sk->sk_sndmsg_off	=	0;

	sk_extended(sk)->sk_peer_pid 	=	NULL;
	sk_extended(sk)->sk_peer_cred	=	NULL;
	sk->sk_write_pending	=	0;
	sk->sk_rcvlowat		=	1;
	sk->sk_rcvtimeo		=	MAX_SCHEDULE_TIMEOUT;
	sk->sk_sndtimeo		=	MAX_SCHEDULE_TIMEOUT;

	sk->sk_stamp = ktime_set(-1L, 0);

	/*
	 * Before updating sk_refcnt, we must commit prior changes to memory
	 * (Documentation/RCU/rculist_nulls.txt for details)
	 */
	smp_wmb();
	atomic_set(&sk->sk_refcnt, 1);
	atomic_set(&sk->sk_drops, 0);
}