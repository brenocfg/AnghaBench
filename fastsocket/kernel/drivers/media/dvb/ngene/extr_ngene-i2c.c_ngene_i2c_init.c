#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ngene {TYPE_2__* pci_dev; TYPE_3__* channel; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {TYPE_1__ dev; void* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {struct i2c_adapter i2c_adapter; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngene_i2c_algo ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int ngene_i2c_init(struct ngene *dev, int dev_nr)
{
	struct i2c_adapter *adap = &(dev->channel[dev_nr].i2c_adapter);

	i2c_set_adapdata(adap, &(dev->channel[dev_nr]));

	strcpy(adap->name, "nGene");

	adap->algo = &ngene_i2c_algo;
	adap->algo_data = (void *)&(dev->channel[dev_nr]);
	adap->dev.parent = &dev->pci_dev->dev;

	return i2c_add_adapter(adap);
}