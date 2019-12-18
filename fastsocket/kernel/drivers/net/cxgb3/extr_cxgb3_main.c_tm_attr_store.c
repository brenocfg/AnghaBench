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
struct port_info {struct adapter* adapter; } ;
struct device {int dummy; } ;
struct adapter {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 unsigned int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 size_t t3_config_sched (struct adapter*,unsigned int,int) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t tm_attr_store(struct device *d,
			     const char *buf, size_t len, int sched)
{
	struct port_info *pi = netdev_priv(to_net_dev(d));
	struct adapter *adap = pi->adapter;
	unsigned int val;
	char *endp;
	ssize_t ret;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	val = simple_strtoul(buf, &endp, 0);
	if (endp == buf || val > 10000000)
		return -EINVAL;

	rtnl_lock();
	ret = t3_config_sched(adap, val, sched);
	if (!ret)
		ret = len;
	rtnl_unlock();
	return ret;
}