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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct ssb_device {struct ssb_bus* bus; } ;
struct ssb_bus {scalar_t__ mmio; struct ssb_device* mapped_device; } ;

/* Variables and functions */
 int ioread8 (scalar_t__) ; 
 int ssb_pci_assert_buspower (struct ssb_bus*) ; 
 int ssb_pci_switch_core (struct ssb_bus*,struct ssb_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u8 ssb_pci_read8(struct ssb_device *dev, u16 offset)
{
	struct ssb_bus *bus = dev->bus;

	if (unlikely(ssb_pci_assert_buspower(bus)))
		return 0xFF;
	if (unlikely(bus->mapped_device != dev)) {
		if (unlikely(ssb_pci_switch_core(bus, dev)))
			return 0xFF;
	}
	return ioread8(bus->mmio + offset);
}