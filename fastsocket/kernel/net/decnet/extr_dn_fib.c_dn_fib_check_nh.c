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
struct rtmsg {scalar_t__ rtm_scope; } ;
struct net_device {int flags; int /*<<< orphan*/ * dn_ptr; } ;
struct flowi {scalar_t__ fld_scope; int /*<<< orphan*/  oif; scalar_t__ fld_dst; } ;
struct dn_fib_res {scalar_t__ type; scalar_t__ scope; } ;
struct dn_fib_nh {int nh_flags; scalar_t__ nh_scope; struct net_device* nh_dev; int /*<<< orphan*/  nh_oif; scalar_t__ nh_gw; } ;
struct dn_fib_info {int dummy; } ;
typedef  int /*<<< orphan*/  fl ;

/* Variables and functions */
 struct net_device* DN_FIB_RES_DEV (struct dn_fib_res) ; 
 int /*<<< orphan*/  DN_FIB_RES_OIF (struct dn_fib_res) ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int ENODEV ; 
 int IFF_UP ; 
 int RTNH_F_ONLINK ; 
 int RTNH_F_PERVASIVE ; 
 scalar_t__ RTN_LOCAL ; 
 scalar_t__ RTN_UNICAST ; 
 scalar_t__ RT_SCOPE_HOST ; 
 scalar_t__ RT_SCOPE_LINK ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int dn_fib_lookup (struct flowi*,struct dn_fib_res*) ; 
 int /*<<< orphan*/  dn_fib_res_put (struct dn_fib_res*) ; 
 scalar_t__ dnet_addr_type (scalar_t__) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dn_fib_check_nh(const struct rtmsg *r, struct dn_fib_info *fi, struct dn_fib_nh *nh)
{
	int err;

	if (nh->nh_gw) {
		struct flowi fl;
		struct dn_fib_res res;

		if (nh->nh_flags&RTNH_F_ONLINK) {
			struct net_device *dev;

			if (r->rtm_scope >= RT_SCOPE_LINK)
				return -EINVAL;
			if (dnet_addr_type(nh->nh_gw) != RTN_UNICAST)
				return -EINVAL;
			if ((dev = __dev_get_by_index(&init_net, nh->nh_oif)) == NULL)
				return -ENODEV;
			if (!(dev->flags&IFF_UP))
				return -ENETDOWN;
			nh->nh_dev = dev;
			dev_hold(dev);
			nh->nh_scope = RT_SCOPE_LINK;
			return 0;
		}

		memset(&fl, 0, sizeof(fl));
		fl.fld_dst = nh->nh_gw;
		fl.oif = nh->nh_oif;
		fl.fld_scope = r->rtm_scope + 1;

		if (fl.fld_scope < RT_SCOPE_LINK)
			fl.fld_scope = RT_SCOPE_LINK;

		if ((err = dn_fib_lookup(&fl, &res)) != 0)
			return err;

		err = -EINVAL;
		if (res.type != RTN_UNICAST && res.type != RTN_LOCAL)
			goto out;
		nh->nh_scope = res.scope;
		nh->nh_oif = DN_FIB_RES_OIF(res);
		nh->nh_dev = DN_FIB_RES_DEV(res);
		if (nh->nh_dev == NULL)
			goto out;
		dev_hold(nh->nh_dev);
		err = -ENETDOWN;
		if (!(nh->nh_dev->flags & IFF_UP))
			goto out;
		err = 0;
out:
		dn_fib_res_put(&res);
		return err;
	} else {
		struct net_device *dev;

		if (nh->nh_flags&(RTNH_F_PERVASIVE|RTNH_F_ONLINK))
			return -EINVAL;

		dev = __dev_get_by_index(&init_net, nh->nh_oif);
		if (dev == NULL || dev->dn_ptr == NULL)
			return -ENODEV;
		if (!(dev->flags&IFF_UP))
			return -ENETDOWN;
		nh->nh_dev = dev;
		dev_hold(nh->nh_dev);
		nh->nh_scope = RT_SCOPE_HOST;
	}

	return 0;
}