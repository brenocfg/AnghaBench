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
struct net_proto_family {int dummy; } ;

/* Variables and functions */
 int BT_MAX_PROTO ; 
 int EEXIST ; 
 int EINVAL ; 
 struct net_proto_family** bt_proto ; 
 int /*<<< orphan*/  bt_proto_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int bt_sock_register(int proto, struct net_proto_family *ops)
{
	int err = 0;

	if (proto < 0 || proto >= BT_MAX_PROTO)
		return -EINVAL;

	write_lock(&bt_proto_lock);

	if (bt_proto[proto])
		err = -EEXIST;
	else
		bt_proto[proto] = ops;

	write_unlock(&bt_proto_lock);

	return err;
}