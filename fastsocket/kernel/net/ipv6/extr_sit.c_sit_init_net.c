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
struct sit_net {int /*<<< orphan*/  fb_tunnel_dev; int /*<<< orphan*/  tunnels_r_l; int /*<<< orphan*/ * tunnels; int /*<<< orphan*/  tunnels_r; int /*<<< orphan*/  tunnels_l; int /*<<< orphan*/  tunnels_wc; } ;
struct net {int dummy; } ;
struct ip_tunnel {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net_set (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipip6_fb_tunnel_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipip6_tunnel_setup ; 
 int /*<<< orphan*/  kfree (struct sit_net*) ; 
 struct sit_net* kzalloc (int,int /*<<< orphan*/ ) ; 
 int net_assign_generic (struct net*,int /*<<< orphan*/ ,struct sit_net*) ; 
 int register_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sit_net_id ; 

__attribute__((used)) static int sit_init_net(struct net *net)
{
	int err;
	struct sit_net *sitn;

	err = -ENOMEM;
	sitn = kzalloc(sizeof(struct sit_net), GFP_KERNEL);
	if (sitn == NULL)
		goto err_alloc;

	err = net_assign_generic(net, sit_net_id, sitn);
	if (err < 0)
		goto err_assign;

	sitn->tunnels[0] = sitn->tunnels_wc;
	sitn->tunnels[1] = sitn->tunnels_l;
	sitn->tunnels[2] = sitn->tunnels_r;
	sitn->tunnels[3] = sitn->tunnels_r_l;

	sitn->fb_tunnel_dev = alloc_netdev(sizeof(struct ip_tunnel), "sit0",
					   ipip6_tunnel_setup);
	if (!sitn->fb_tunnel_dev) {
		err = -ENOMEM;
		goto err_alloc_dev;
	}
	dev_net_set(sitn->fb_tunnel_dev, net);

	ipip6_fb_tunnel_init(sitn->fb_tunnel_dev);

	if ((err = register_netdev(sitn->fb_tunnel_dev)))
		goto err_reg_dev;

	return 0;

err_reg_dev:
	dev_put(sitn->fb_tunnel_dev);
	free_netdev(sitn->fb_tunnel_dev);
err_alloc_dev:
	/* nothing */
err_assign:
	kfree(sitn);
err_alloc:
	return err;
}