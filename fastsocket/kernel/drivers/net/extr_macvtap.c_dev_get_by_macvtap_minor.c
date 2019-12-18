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
struct macvlan_dev {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct macvlan_dev* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  minor_idr ; 
 int /*<<< orphan*/  minor_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device *dev_get_by_macvtap_minor(int minor)
{
       struct net_device *dev = NULL;
       struct macvlan_dev *vlan;

       mutex_lock(&minor_lock);
       vlan = idr_find(&minor_idr, minor);
       if (vlan) {
               dev = vlan->dev;
               dev_hold(dev);
       }
       mutex_unlock(&minor_lock);
       return dev;
}