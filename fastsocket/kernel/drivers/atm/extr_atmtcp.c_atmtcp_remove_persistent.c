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
struct atmtcp_dev_data {scalar_t__ vcc; scalar_t__ persist; } ;
struct atm_dev {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int EMEDIUMTYPE ; 
 int ENODEV ; 
 struct atmtcp_dev_data* PRIV (struct atm_dev*) ; 
 int /*<<< orphan*/  atm_dev_deregister (struct atm_dev*) ; 
 struct atm_dev* atm_dev_lookup (int) ; 
 int /*<<< orphan*/  atm_dev_put (struct atm_dev*) ; 
 int /*<<< orphan*/  atmtcp_v_dev_ops ; 
 int /*<<< orphan*/  kfree (struct atmtcp_dev_data*) ; 

__attribute__((used)) static int atmtcp_remove_persistent(int itf)
{
	struct atm_dev *dev;
	struct atmtcp_dev_data *dev_data;

	dev = atm_dev_lookup(itf);
	if (!dev) return -ENODEV;
	if (dev->ops != &atmtcp_v_dev_ops) {
		atm_dev_put(dev);
		return -EMEDIUMTYPE;
	}
	dev_data = PRIV(dev);
	if (!dev_data->persist) return 0;
	dev_data->persist = 0;
	if (PRIV(dev)->vcc) return 0;
	kfree(dev_data);
	atm_dev_put(dev);
	atm_dev_deregister(dev);
	return 0;
}