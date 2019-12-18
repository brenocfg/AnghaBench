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
struct i2o_dma {int /*<<< orphan*/ * virt; scalar_t__ phys; int /*<<< orphan*/  len; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void i2o_dma_free(struct device *dev, struct i2o_dma *addr)
{
	if (addr->virt) {
		if (addr->phys)
			dma_free_coherent(dev, addr->len, addr->virt,
					  addr->phys);
		else
			kfree(addr->virt);
		addr->virt = NULL;
	}
}