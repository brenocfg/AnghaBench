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
struct rtnl_link_ops {scalar_t__ (* get_xstats_size ) (struct net_device const*) ;scalar_t__ (* get_size ) (struct net_device const*) ;int /*<<< orphan*/  kind; } ;
struct nlattr {int dummy; } ;
struct net_device {struct rtnl_link_ops* rtnl_link_ops; } ;

/* Variables and functions */
 size_t nlmsg_total_size (int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct net_device const*) ; 
 scalar_t__ stub2 (struct net_device const*) ; 

__attribute__((used)) static size_t rtnl_link_get_size(const struct net_device *dev)
{
	const struct rtnl_link_ops *ops = dev->rtnl_link_ops;
	size_t size;

	if (!ops)
		return 0;

	size = nlmsg_total_size(sizeof(struct nlattr)) + /* IFLA_LINKINFO */
	       nlmsg_total_size(strlen(ops->kind) + 1);	 /* IFLA_INFO_KIND */

	if (ops->get_size)
		/* IFLA_INFO_DATA + nested data */
		size += nlmsg_total_size(sizeof(struct nlattr)) +
			ops->get_size(dev);

	if (ops->get_xstats_size)
		size += ops->get_xstats_size(dev);	/* IFLA_INFO_XSTATS */

	return size;
}