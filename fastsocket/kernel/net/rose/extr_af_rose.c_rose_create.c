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
struct rose_sock {int /*<<< orphan*/  state; void* idle; void* hb; void* t3; void* t2; void* t1; int /*<<< orphan*/  idletimer; int /*<<< orphan*/  timer; scalar_t__ fraglen; int /*<<< orphan*/  frag_queue; int /*<<< orphan*/  ack_queue; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PF_ROSE ; 
 int /*<<< orphan*/  ROSE_STATE_0 ; 
 scalar_t__ SOCK_SEQPACKET ; 
 struct net init_net ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rose_proto ; 
 int /*<<< orphan*/  rose_proto_ops ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sysctl_rose_ack_hold_back_timeout ; 
 int /*<<< orphan*/  sysctl_rose_call_request_timeout ; 
 int /*<<< orphan*/  sysctl_rose_clear_request_timeout ; 
 int /*<<< orphan*/  sysctl_rose_no_activity_timeout ; 
 int /*<<< orphan*/  sysctl_rose_reset_request_timeout ; 

__attribute__((used)) static int rose_create(struct net *net, struct socket *sock, int protocol,
		       int kern)
{
	struct sock *sk;
	struct rose_sock *rose;

	if (net != &init_net)
		return -EAFNOSUPPORT;

	if (sock->type != SOCK_SEQPACKET || protocol != 0)
		return -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, PF_ROSE, GFP_ATOMIC, &rose_proto);
	if (sk == NULL)
		return -ENOMEM;

	rose = rose_sk(sk);

	sock_init_data(sock, sk);

	skb_queue_head_init(&rose->ack_queue);
#ifdef M_BIT
	skb_queue_head_init(&rose->frag_queue);
	rose->fraglen    = 0;
#endif

	sock->ops    = &rose_proto_ops;
	sk->sk_protocol = protocol;

	init_timer(&rose->timer);
	init_timer(&rose->idletimer);

	rose->t1   = msecs_to_jiffies(sysctl_rose_call_request_timeout);
	rose->t2   = msecs_to_jiffies(sysctl_rose_reset_request_timeout);
	rose->t3   = msecs_to_jiffies(sysctl_rose_clear_request_timeout);
	rose->hb   = msecs_to_jiffies(sysctl_rose_ack_hold_back_timeout);
	rose->idle = msecs_to_jiffies(sysctl_rose_no_activity_timeout);

	rose->state = ROSE_STATE_0;

	return 0;
}