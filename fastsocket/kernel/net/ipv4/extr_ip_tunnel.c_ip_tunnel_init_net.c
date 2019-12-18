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
struct rtnl_link_ops {int dummy; } ;
struct net {int dummy; } ;
struct ip_tunnel_parm {int /*<<< orphan*/  name; } ;
struct ip_tunnel_net {int /*<<< orphan*/ * fb_tunnel_dev; int /*<<< orphan*/  tunnels; } ;
struct hlist_head {int dummy; } ;
typedef  int /*<<< orphan*/  parms ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int IP_TNL_HASH_SIZE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * __ip_tunnel_create (struct net*,struct rtnl_link_ops*,struct ip_tunnel_parm*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ip_tunnel_parm*,int /*<<< orphan*/ ,int) ; 
 struct ip_tunnel_net* net_generic (struct net*,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int ip_tunnel_init_net(struct net *net, int ip_tnl_net_id,
				  struct rtnl_link_ops *ops, char *devname)
{
	struct ip_tunnel_net *itn = net_generic(net, ip_tnl_net_id);
	struct ip_tunnel_parm parms;

	itn->tunnels = kzalloc(IP_TNL_HASH_SIZE * sizeof(struct hlist_head), GFP_KERNEL);
	if (!itn->tunnels)
		return -ENOMEM;

	if (!ops) {
		itn->fb_tunnel_dev = NULL;
		return 0;
	}
	memset(&parms, 0, sizeof(parms));
	if (devname)
		strlcpy(parms.name, devname, IFNAMSIZ);

	rtnl_lock();
	itn->fb_tunnel_dev = __ip_tunnel_create(net, ops, &parms);
	rtnl_unlock();
	if (IS_ERR(itn->fb_tunnel_dev)) {
		kfree(itn->tunnels);
		return PTR_ERR(itn->fb_tunnel_dev);
	}

	return 0;
}