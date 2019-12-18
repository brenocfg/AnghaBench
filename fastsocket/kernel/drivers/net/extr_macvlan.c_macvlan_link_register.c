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
struct rtnl_link_ops {int priv_size; int /*<<< orphan*/  fill_info; int /*<<< orphan*/  get_size; int /*<<< orphan*/  changelink; int /*<<< orphan*/  policy; int /*<<< orphan*/  maxtype; int /*<<< orphan*/  validate; int /*<<< orphan*/  get_tx_queues; } ;
struct macvlan_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLA_MACVLAN_MAX ; 
 int /*<<< orphan*/  macvlan_changelink ; 
 int /*<<< orphan*/  macvlan_fill_info ; 
 int /*<<< orphan*/  macvlan_get_size ; 
 int /*<<< orphan*/  macvlan_get_tx_queues ; 
 int /*<<< orphan*/  macvlan_policy ; 
 int /*<<< orphan*/  macvlan_validate ; 
 int rtnl_link_register (struct rtnl_link_ops*) ; 

int macvlan_link_register(struct rtnl_link_ops *ops)
{
	/* common fields */
	ops->priv_size		= sizeof(struct macvlan_dev);
	ops->get_tx_queues	= macvlan_get_tx_queues;
	ops->validate		= macvlan_validate;
	ops->maxtype		= IFLA_MACVLAN_MAX;
	ops->policy		= macvlan_policy;
	ops->changelink		= macvlan_changelink;
	ops->get_size		= macvlan_get_size;
	ops->fill_info		= macvlan_fill_info;

	return rtnl_link_register(ops);
}