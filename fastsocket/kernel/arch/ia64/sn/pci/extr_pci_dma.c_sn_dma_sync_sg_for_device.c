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
struct scatterlist {int dummy; } ;
struct device {int /*<<< orphan*/ * bus; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  pci_bus_type ; 

__attribute__((used)) static void sn_dma_sync_sg_for_device(struct device *dev, struct scatterlist *sg,
				      int nelems, enum dma_data_direction dir)
{
	BUG_ON(dev->bus != &pci_bus_type);
}