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
struct socket {int /*<<< orphan*/  wait; struct sock* sk; } ;
struct sock {int sk_state; int /*<<< orphan*/  sk_receive_queue; } ;
struct pep_sock {int /*<<< orphan*/  tx_credits; int /*<<< orphan*/  ctrlreq_queue; int /*<<< orphan*/  ackq; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLPRI ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRBAND ; 
 unsigned int POLLWRNORM ; 
#define  TCP_CLOSE 129 
 int TCP_CLOSE_WAIT ; 
 int TCP_ESTABLISHED ; 
#define  TCP_LISTEN 128 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int pn_socket_poll(struct file *file, struct socket *sock,
					poll_table *wait)
{
	struct sock *sk = sock->sk;
	struct pep_sock *pn = pep_sk(sk);
	unsigned int mask = 0;

	poll_wait(file, &sock->wait, wait);

	switch (sk->sk_state) {
	case TCP_LISTEN:
		return hlist_empty(&pn->ackq) ? 0 : POLLIN;
	case TCP_CLOSE:
		return POLLERR;
	}

	if (!skb_queue_empty(&sk->sk_receive_queue))
		mask |= POLLIN | POLLRDNORM;
	if (!skb_queue_empty(&pn->ctrlreq_queue))
		mask |= POLLPRI;
	if (!mask && sk->sk_state == TCP_CLOSE_WAIT)
		return POLLHUP;

	if (sk->sk_state == TCP_ESTABLISHED && atomic_read(&pn->tx_credits))
		mask |= POLLOUT | POLLWRNORM | POLLWRBAND;

	return mask;
}