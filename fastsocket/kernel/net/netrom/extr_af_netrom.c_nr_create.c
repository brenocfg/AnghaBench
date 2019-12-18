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
struct socket {scalar_t__ type; int /*<<< orphan*/ * ops; } ;
struct sock {int sk_protocol; } ;
struct nr_sock {int bpqext; int /*<<< orphan*/  state; int /*<<< orphan*/  window; void* idle; void* t4; void* n2; void* t2; void* t1; int /*<<< orphan*/  frag_queue; int /*<<< orphan*/  reseq_queue; int /*<<< orphan*/  ack_queue; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NR_STATE_0 ; 
 int /*<<< orphan*/  PF_NETROM ; 
 scalar_t__ SOCK_SEQPACKET ; 
 struct net init_net ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_init_timers (struct sock*) ; 
 int /*<<< orphan*/  nr_proto ; 
 int /*<<< orphan*/  nr_proto_ops ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sysctl_netrom_transport_acknowledge_delay ; 
 int /*<<< orphan*/  sysctl_netrom_transport_busy_delay ; 
 int /*<<< orphan*/  sysctl_netrom_transport_maximum_tries ; 
 int /*<<< orphan*/  sysctl_netrom_transport_no_activity_timeout ; 
 int /*<<< orphan*/  sysctl_netrom_transport_requested_window_size ; 
 int /*<<< orphan*/  sysctl_netrom_transport_timeout ; 

__attribute__((used)) static int nr_create(struct net *net, struct socket *sock, int protocol,
		     int kern)
{
	struct sock *sk;
	struct nr_sock *nr;

	if (net != &init_net)
		return -EAFNOSUPPORT;

	if (sock->type != SOCK_SEQPACKET || protocol != 0)
		return -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, PF_NETROM, GFP_ATOMIC, &nr_proto);
	if (sk  == NULL)
		return -ENOMEM;

	nr = nr_sk(sk);

	sock_init_data(sock, sk);

	sock->ops    = &nr_proto_ops;
	sk->sk_protocol = protocol;

	skb_queue_head_init(&nr->ack_queue);
	skb_queue_head_init(&nr->reseq_queue);
	skb_queue_head_init(&nr->frag_queue);

	nr_init_timers(sk);

	nr->t1     =
		msecs_to_jiffies(sysctl_netrom_transport_timeout);
	nr->t2     =
		msecs_to_jiffies(sysctl_netrom_transport_acknowledge_delay);
	nr->n2     =
		msecs_to_jiffies(sysctl_netrom_transport_maximum_tries);
	nr->t4     =
		msecs_to_jiffies(sysctl_netrom_transport_busy_delay);
	nr->idle   =
		msecs_to_jiffies(sysctl_netrom_transport_no_activity_timeout);
	nr->window = sysctl_netrom_transport_requested_window_size;

	nr->bpqext = 1;
	nr->state  = NR_STATE_0;

	return 0;
}