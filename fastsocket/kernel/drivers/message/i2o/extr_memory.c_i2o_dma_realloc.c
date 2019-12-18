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
struct i2o_dma {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int i2o_dma_alloc (struct device*,struct i2o_dma*,size_t) ; 
 int /*<<< orphan*/  i2o_dma_free (struct device*,struct i2o_dma*) ; 

int i2o_dma_realloc(struct device *dev, struct i2o_dma *addr, size_t len)
{
	i2o_dma_free(dev, addr);

	if (len)
		return i2o_dma_alloc(dev, addr, len);

	return 0;
}