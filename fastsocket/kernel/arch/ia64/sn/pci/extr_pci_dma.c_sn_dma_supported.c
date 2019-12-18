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
typedef  int u64 ;
struct device {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  pci_bus_type ; 

__attribute__((used)) static int sn_dma_supported(struct device *dev, u64 mask)
{
	BUG_ON(dev->bus != &pci_bus_type);

	if (mask < 0x7fffffff)
		return 0;
	return 1;
}