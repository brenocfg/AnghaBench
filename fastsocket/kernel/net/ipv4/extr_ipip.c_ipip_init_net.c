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
struct net {int dummy; } ;
struct ipip_net {int /*<<< orphan*/  fb_tunnel_dev; int /*<<< orphan*/  tunnels_r_l; int /*<<< orphan*/ * tunnels; int /*<<< orphan*/  tunnels_r; int /*<<< orphan*/  tunnels_l; int /*<<< orphan*/  tunnels_wc; } ;
struct ip_tunnel {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net_set (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipip_fb_tunnel_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipip_net_id ; 
 int /*<<< orphan*/  ipip_tunnel_setup ; 
 int /*<<< orphan*/  kfree (struct ipip_net*) ; 
 struct ipip_net* kzalloc (int,int /*<<< orphan*/ ) ; 
 int net_assign_generic (struct net*,int /*<<< orphan*/ ,struct ipip_net*) ; 
 int register_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipip_init_net(struct net *net)
{
	int err;
	struct ipip_net *ipn;

	err = -ENOMEM;
	ipn = kzalloc(sizeof(struct ipip_net), GFP_KERNEL);
	if (ipn == NULL)
		goto err_alloc;

	err = net_assign_generic(net, ipip_net_id, ipn);
	if (err < 0)
		goto err_assign;

	ipn->tunnels[0] = ipn->tunnels_wc;
	ipn->tunnels[1] = ipn->tunnels_l;
	ipn->tunnels[2] = ipn->tunnels_r;
	ipn->tunnels[3] = ipn->tunnels_r_l;

	ipn->fb_tunnel_dev = alloc_netdev(sizeof(struct ip_tunnel),
					   "tunl0",
					   ipip_tunnel_setup);
	if (!ipn->fb_tunnel_dev) {
		err = -ENOMEM;
		goto err_alloc_dev;
	}
	dev_net_set(ipn->fb_tunnel_dev, net);

	ipip_fb_tunnel_init(ipn->fb_tunnel_dev);

	if ((err = register_netdev(ipn->fb_tunnel_dev)))
		goto err_reg_dev;

	return 0;

err_reg_dev:
	free_netdev(ipn->fb_tunnel_dev);
err_alloc_dev:
	/* nothing */
err_assign:
	kfree(ipn);
err_alloc:
	return err;
}