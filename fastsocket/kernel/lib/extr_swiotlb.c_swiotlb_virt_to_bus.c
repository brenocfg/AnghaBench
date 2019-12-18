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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (void volatile*) ; 

__attribute__((used)) static dma_addr_t swiotlb_virt_to_bus(struct device *hwdev,
				      volatile void *address)
{
	return phys_to_dma(hwdev, virt_to_phys(address));
}