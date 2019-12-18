#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct atmtcp_dev_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vci_bits; int /*<<< orphan*/  vpi_bits; } ;
struct atm_dev {struct atmtcp_dev_data* dev_data; TYPE_1__ ci_range; } ;
struct TYPE_4__ {int persist; int /*<<< orphan*/ * vcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_LABEL ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_VCI_BITS ; 
 int /*<<< orphan*/  MAX_VPI_BITS ; 
 TYPE_2__* PRIV (struct atm_dev*) ; 
 struct atm_dev* atm_dev_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atmtcp_v_dev_ops ; 
 int /*<<< orphan*/  kfree (struct atmtcp_dev_data*) ; 
 struct atmtcp_dev_data* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmtcp_create(int itf,int persist,struct atm_dev **result)
{
	struct atmtcp_dev_data *dev_data;
	struct atm_dev *dev;

	dev_data = kmalloc(sizeof(*dev_data),GFP_KERNEL);
	if (!dev_data)
		return -ENOMEM;

	dev = atm_dev_register(DEV_LABEL,&atmtcp_v_dev_ops,itf,NULL);
	if (!dev) {
		kfree(dev_data);
		return itf == -1 ? -ENOMEM : -EBUSY;
	}
	dev->ci_range.vpi_bits = MAX_VPI_BITS;
	dev->ci_range.vci_bits = MAX_VCI_BITS;
	dev->dev_data = dev_data;
	PRIV(dev)->vcc = NULL;
	PRIV(dev)->persist = persist;
	if (result) *result = dev;
	return 0;
}