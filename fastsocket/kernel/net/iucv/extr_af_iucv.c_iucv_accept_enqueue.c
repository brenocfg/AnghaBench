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
struct sock {int /*<<< orphan*/  sk_ack_backlog; } ;
struct iucv_sock {struct sock* parent; int /*<<< orphan*/  accept_q_lock; int /*<<< orphan*/  accept_q; } ;

/* Variables and functions */
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void iucv_accept_enqueue(struct sock *parent, struct sock *sk)
{
	unsigned long flags;
	struct iucv_sock *par = iucv_sk(parent);

	sock_hold(sk);
	spin_lock_irqsave(&par->accept_q_lock, flags);
	list_add_tail(&iucv_sk(sk)->accept_q, &par->accept_q);
	spin_unlock_irqrestore(&par->accept_q_lock, flags);
	iucv_sk(sk)->parent = parent;
	parent->sk_ack_backlog++;
}