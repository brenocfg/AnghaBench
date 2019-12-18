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
struct ipx_interface {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct ipx_interface* __ipxitf_find_using_phys (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipx_interfaces_lock ; 
 int /*<<< orphan*/  ipxitf_hold (struct ipx_interface*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ipx_interface *ipxitf_find_using_phys(struct net_device *dev,
						    __be16 datalink)
{
	struct ipx_interface *i;

	spin_lock_bh(&ipx_interfaces_lock);
	i = __ipxitf_find_using_phys(dev, datalink);
	if (i)
		ipxitf_hold(i);
	spin_unlock_bh(&ipx_interfaces_lock);
	return i;
}