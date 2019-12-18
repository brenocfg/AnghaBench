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
struct vhost_net {scalar_t__ tx_poll_state; scalar_t__ poll; } ;
struct socket {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 scalar_t__ VHOST_NET_POLL_STARTED ; 
 scalar_t__ VHOST_NET_POLL_STOPPED ; 
 scalar_t__ VHOST_NET_VQ_TX ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vhost_poll_start (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_poll_start(struct vhost_net *net, struct socket *sock)
{
	if (unlikely(net->tx_poll_state != VHOST_NET_POLL_STOPPED))
		return;
	vhost_poll_start(net->poll + VHOST_NET_VQ_TX, sock->file);
	net->tx_poll_state = VHOST_NET_POLL_STARTED;
}