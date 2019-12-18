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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct l2cap_chan_list {struct sock* head; } ;
struct TYPE_2__ {scalar_t__ ident; struct sock* next_c; } ;

/* Variables and functions */
 TYPE_1__* l2cap_pi (struct sock*) ; 

__attribute__((used)) static struct sock *__l2cap_get_chan_by_ident(struct l2cap_chan_list *l, u8 ident)
{
	struct sock *s;
	for (s = l->head; s; s = l2cap_pi(s)->next_c) {
		if (l2cap_pi(s)->ident == ident)
			break;
	}
	return s;
}