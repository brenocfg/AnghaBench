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
typedef  int u32 ;
struct netlbl_unlhsh_iface {int dummy; } ;
struct netlbl_audit {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct net_device* dev_get_by_name (struct net*,char const*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  netlabel_mgmt_protocount ; 
 int /*<<< orphan*/  netlbl_unlhsh_condremove_iface (struct netlbl_unlhsh_iface*) ; 
 int /*<<< orphan*/  netlbl_unlhsh_def ; 
 int netlbl_unlhsh_remove_addr4 (struct net*,struct netlbl_unlhsh_iface*,void const*,void const*,struct netlbl_audit*) ; 
 int netlbl_unlhsh_remove_addr6 (struct net*,struct netlbl_unlhsh_iface*,void const*,void const*,struct netlbl_audit*) ; 
 struct netlbl_unlhsh_iface* netlbl_unlhsh_search_iface (int /*<<< orphan*/ ) ; 
 struct netlbl_unlhsh_iface* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int netlbl_unlhsh_remove(struct net *net,
			 const char *dev_name,
			 const void *addr,
			 const void *mask,
			 u32 addr_len,
			 struct netlbl_audit *audit_info)
{
	int ret_val;
	struct net_device *dev;
	struct netlbl_unlhsh_iface *iface;

	if (addr_len != sizeof(struct in_addr) &&
	    addr_len != sizeof(struct in6_addr))
		return -EINVAL;

	rcu_read_lock();
	if (dev_name != NULL) {
		dev = dev_get_by_name(net, dev_name);
		if (dev == NULL) {
			ret_val = -ENODEV;
			goto unlhsh_remove_return;
		}
		iface = netlbl_unlhsh_search_iface(dev->ifindex);
		dev_put(dev);
	} else
		iface = rcu_dereference(netlbl_unlhsh_def);
	if (iface == NULL) {
		ret_val = -ENOENT;
		goto unlhsh_remove_return;
	}
	switch (addr_len) {
	case sizeof(struct in_addr):
		ret_val = netlbl_unlhsh_remove_addr4(net,
						     iface, addr, mask,
						     audit_info);
		break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case sizeof(struct in6_addr):
		ret_val = netlbl_unlhsh_remove_addr6(net,
						     iface, addr, mask,
						     audit_info);
		break;
#endif /* IPv6 */
	default:
		ret_val = -EINVAL;
	}
	if (ret_val == 0) {
		netlbl_unlhsh_condremove_iface(iface);
		atomic_dec(&netlabel_mgmt_protocount);
	}

unlhsh_remove_return:
	rcu_read_unlock();
	return ret_val;
}