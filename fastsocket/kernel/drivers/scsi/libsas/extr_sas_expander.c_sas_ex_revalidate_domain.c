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
struct expander_device {int num_phys; } ;
struct domain_device {struct expander_device ex_dev; } ;

/* Variables and functions */
 int sas_find_bcast_dev (struct domain_device*,struct domain_device**) ; 
 int sas_find_bcast_phy (struct domain_device*,int*,int,int) ; 
 int sas_rediscover (struct domain_device*,int) ; 

int sas_ex_revalidate_domain(struct domain_device *port_dev)
{
	int res;
	struct domain_device *dev = NULL;

	res = sas_find_bcast_dev(port_dev, &dev);
	while (res == 0 && dev) {
		struct expander_device *ex = &dev->ex_dev;
		int i = 0, phy_id;

		do {
			phy_id = -1;
			res = sas_find_bcast_phy(dev, &phy_id, i, true);
			if (phy_id == -1)
				break;
			res = sas_rediscover(dev, phy_id);
			i = phy_id + 1;
		} while (i < ex->num_phys);

		dev = NULL;
		res = sas_find_bcast_dev(port_dev, &dev);
	}
	return res;
}