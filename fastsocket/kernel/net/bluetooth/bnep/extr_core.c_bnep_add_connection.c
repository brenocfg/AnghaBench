#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u8 ;
struct socket {int /*<<< orphan*/  sk; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  broadcast; int /*<<< orphan*/ ** dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  msg_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** h_dest; int /*<<< orphan*/ ** h_source; } ;
struct bnep_session {scalar_t__ state; int /*<<< orphan*/  mc_filter; TYPE_2__ msg; int /*<<< orphan*/  role; struct socket* sock; struct net_device* dev; TYPE_1__ eh; } ;
struct bnep_connadd_req {char* device; int /*<<< orphan*/  role; } ;
struct TYPE_6__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  CLONE_KERNEL ; 
 int EEXIST ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 struct bnep_session* __bnep_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __bnep_link_session (struct bnep_session*) ; 
 int /*<<< orphan*/  __bnep_unlink_session (struct bnep_session*) ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  baswap (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnep_get_device (struct bnep_session*) ; 
 int /*<<< orphan*/  bnep_mc_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnep_net_setup ; 
 int /*<<< orphan*/  bnep_session ; 
 int /*<<< orphan*/  bnep_session_sem ; 
 int /*<<< orphan*/  bnep_set_default_proto_filter (struct bnep_session*) ; 
 int /*<<< orphan*/  bnep_type ; 
 TYPE_3__* bt_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int kernel_thread (int /*<<< orphan*/ ,struct bnep_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 struct bnep_session* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int bnep_add_connection(struct bnep_connadd_req *req, struct socket *sock)
{
	struct net_device *dev;
	struct bnep_session *s, *ss;
	u8 dst[ETH_ALEN], src[ETH_ALEN];
	int err;

	BT_DBG("");

	baswap((void *) dst, &bt_sk(sock->sk)->dst);
	baswap((void *) src, &bt_sk(sock->sk)->src);

	/* session struct allocated as private part of net_device */
	dev = alloc_netdev(sizeof(struct bnep_session),
			   (*req->device) ? req->device : "bnep%d",
			   bnep_net_setup);
	if (!dev)
		return -ENOMEM;

	down_write(&bnep_session_sem);

	ss = __bnep_get_session(dst);
	if (ss && ss->state == BT_CONNECTED) {
		err = -EEXIST;
		goto failed;
	}

	s = netdev_priv(dev);

	/* This is rx header therefore addresses are swapped.
	 * ie eh.h_dest is our local address. */
	memcpy(s->eh.h_dest,   &src, ETH_ALEN);
	memcpy(s->eh.h_source, &dst, ETH_ALEN);
	memcpy(dev->dev_addr, s->eh.h_dest, ETH_ALEN);

	s->dev   = dev;
	s->sock  = sock;
	s->role  = req->role;
	s->state = BT_CONNECTED;

	s->msg.msg_flags = MSG_NOSIGNAL;

#ifdef CONFIG_BT_BNEP_MC_FILTER
	/* Set default mc filter */
	set_bit(bnep_mc_hash(dev->broadcast), (ulong *) &s->mc_filter);
#endif

#ifdef CONFIG_BT_BNEP_PROTO_FILTER
	/* Set default protocol filter */
	bnep_set_default_proto_filter(s);
#endif

	SET_NETDEV_DEV(dev, bnep_get_device(s));
	SET_NETDEV_DEVTYPE(dev, &bnep_type);

	err = register_netdev(dev);
	if (err) {
		goto failed;
	}

	__bnep_link_session(s);

	err = kernel_thread(bnep_session, s, CLONE_KERNEL);
	if (err < 0) {
		/* Session thread start failed, gotta cleanup. */
		unregister_netdev(dev);
		__bnep_unlink_session(s);
		goto failed;
	}

	up_write(&bnep_session_sem);
	strcpy(req->device, dev->name);
	return 0;

failed:
	up_write(&bnep_session_sem);
	free_netdev(dev);
	return err;
}