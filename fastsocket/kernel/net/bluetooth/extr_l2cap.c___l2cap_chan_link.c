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
struct sock {int dummy; } ;
struct l2cap_chan_list {struct sock* head; } ;
struct TYPE_2__ {struct sock* prev_c; struct sock* next_c; } ;

/* Variables and functions */
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

__attribute__((used)) static inline void __l2cap_chan_link(struct l2cap_chan_list *l, struct sock *sk)
{
	sock_hold(sk);

	if (l->head)
		l2cap_pi(l->head)->prev_c = sk;

	l2cap_pi(sk)->next_c = l->head;
	l2cap_pi(sk)->prev_c = NULL;
	l->head = sk;
}