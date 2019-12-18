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
struct socket {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int (* create ) (struct net*,struct socket*,int,int) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int BT_MAX_PROTO ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 TYPE_1__** bt_proto ; 
 int /*<<< orphan*/  bt_proto_lock ; 
 int /*<<< orphan*/  bt_sock_reclassify_lock (struct socket*,int) ; 
 struct net init_net ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_module (char*,int) ; 
 int stub1 (struct net*,struct socket*,int,int) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bt_sock_create(struct net *net, struct socket *sock, int proto,
			  int kern)
{
	int err;

	if (net != &init_net)
		return -EAFNOSUPPORT;

	if (proto < 0 || proto >= BT_MAX_PROTO)
		return -EINVAL;

	if (!bt_proto[proto])
		request_module("bt-proto-%d", proto);

	err = -EPROTONOSUPPORT;

	read_lock(&bt_proto_lock);

	if (bt_proto[proto] && try_module_get(bt_proto[proto]->owner)) {
		err = bt_proto[proto]->create(net, sock, proto, kern);
		bt_sock_reclassify_lock(sock, proto);
		module_put(bt_proto[proto]->owner);
	}

	read_unlock(&bt_proto_lock);

	return err;
}