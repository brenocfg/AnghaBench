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
struct sock {int /*<<< orphan*/  sk_state; TYPE_1__* sk_prot; scalar_t__ sk_ack_backlog; scalar_t__ sk_max_ack_backlog; } ;
struct inet_sock {int /*<<< orphan*/  num; int /*<<< orphan*/  sport; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_accept_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hash ) (struct sock*) ;int /*<<< orphan*/  (* get_port ) (struct sock*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EADDRINUSE ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  TCP_LISTEN ; 
 int /*<<< orphan*/  __reqsk_queue_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_delack_init (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int reqsk_queue_alloc (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  sk_dst_reset (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

int inet_csk_listen_start(struct sock *sk, const int nr_table_entries)
{
	struct inet_sock *inet = inet_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);
	int rc = reqsk_queue_alloc(&icsk->icsk_accept_queue, nr_table_entries);

	if (rc != 0)
		return rc;

	sk->sk_max_ack_backlog = 0;
	sk->sk_ack_backlog = 0;
	inet_csk_delack_init(sk);

	/* There is race window here: we announce ourselves listening,
	 * but this transition is still not validated by get_port().
	 * It is OK, because this socket enters to hash table only
	 * after validation is complete.
	 */
	sk->sk_state = TCP_LISTEN;
	if (!sk->sk_prot->get_port(sk, inet->num)) {
		inet->sport = htons(inet->num);

		sk_dst_reset(sk);
		sk->sk_prot->hash(sk);

		return 0;
	}

	sk->sk_state = TCP_CLOSE;
	__reqsk_queue_destroy(&icsk->icsk_accept_queue);
	return -EADDRINUSE;
}