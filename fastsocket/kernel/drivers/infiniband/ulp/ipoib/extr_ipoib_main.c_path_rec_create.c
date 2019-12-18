#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  raw; } ;
struct TYPE_6__ {int numb_path; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  pkey; int /*<<< orphan*/  sgid; TYPE_1__ dgid; } ;
struct ipoib_path {TYPE_2__ pathrec; int /*<<< orphan*/  neigh_list; int /*<<< orphan*/  queue; struct net_device* dev; } ;
struct ipoib_dev_priv {TYPE_4__* broadcast; int /*<<< orphan*/  pkey; int /*<<< orphan*/  local_gid; } ;
struct TYPE_7__ {int /*<<< orphan*/  traffic_class; } ;
struct TYPE_8__ {TYPE_3__ mcmember; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct ipoib_path* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ipoib_path *path_rec_create(struct net_device *dev, void *gid)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_path *path;

	if (!priv->broadcast)
		return NULL;

	path = kzalloc(sizeof *path, GFP_ATOMIC);
	if (!path)
		return NULL;

	path->dev = dev;

	skb_queue_head_init(&path->queue);

	INIT_LIST_HEAD(&path->neigh_list);

	memcpy(path->pathrec.dgid.raw, gid, sizeof (union ib_gid));
	path->pathrec.sgid	    = priv->local_gid;
	path->pathrec.pkey	    = cpu_to_be16(priv->pkey);
	path->pathrec.numb_path     = 1;
	path->pathrec.traffic_class = priv->broadcast->mcmember.traffic_class;

	return path;
}