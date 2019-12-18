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
struct net_device {int dummy; } ;
struct ipx_interface_definition {scalar_t__ ipx_special; int /*<<< orphan*/  ipx_device; int /*<<< orphan*/  ipx_dlink_type; } ;
struct ipx_interface {int dummy; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int EPROTONOSUPPORT ; 
 scalar_t__ IPX_INTERNAL ; 
 struct net_device* __dev_get_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ipx_interface* __ipxitf_find_using_phys (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  __ipxitf_put (struct ipx_interface*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  ipx_interfaces_lock ; 
 struct ipx_interface* ipx_internal_net ; 
 scalar_t__ ipx_map_frame_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipxitf_delete(struct ipx_interface_definition *idef)
{
	struct net_device *dev = NULL;
	__be16 dlink_type = 0;
	struct ipx_interface *intrfc;
	int rc = 0;

	spin_lock_bh(&ipx_interfaces_lock);
	if (idef->ipx_special == IPX_INTERNAL) {
		if (ipx_internal_net) {
			__ipxitf_put(ipx_internal_net);
			goto out;
		}
		rc = -ENOENT;
		goto out;
	}

	dlink_type = ipx_map_frame_type(idef->ipx_dlink_type);
	rc = -EPROTONOSUPPORT;
	if (!dlink_type)
		goto out;

	dev = __dev_get_by_name(&init_net, idef->ipx_device);
	rc = -ENODEV;
	if (!dev)
		goto out;

	intrfc = __ipxitf_find_using_phys(dev, dlink_type);
	rc = -EINVAL;
	if (!intrfc)
		goto out;
	__ipxitf_put(intrfc);

	rc = 0;
out:
	spin_unlock_bh(&ipx_interfaces_lock);
	return rc;
}