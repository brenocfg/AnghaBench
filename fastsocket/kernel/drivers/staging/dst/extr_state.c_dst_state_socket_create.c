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
struct socket {TYPE_1__* sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa_family; } ;
struct dst_network_ctl {int /*<<< orphan*/  proto; int /*<<< orphan*/  type; TYPE_2__ addr; } ;
struct dst_state {struct socket* read_socket; struct socket* socket; struct dst_network_ctl ctl; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/  sk_rcvtimeo; int /*<<< orphan*/  sk_sndtimeo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_DEFAULT_TIMEO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int sock_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 

int dst_state_socket_create(struct dst_state *st)
{
	int err;
	struct socket *sock;
	struct dst_network_ctl *ctl = &st->ctl;

	err = sock_create(ctl->addr.sa_family, ctl->type, ctl->proto, &sock);
	if (err < 0)
		return err;

	sock->sk->sk_sndtimeo = sock->sk->sk_rcvtimeo =
		msecs_to_jiffies(DST_DEFAULT_TIMEO);
	sock->sk->sk_allocation = GFP_NOIO;

	st->socket = st->read_socket = sock;
	return 0;
}