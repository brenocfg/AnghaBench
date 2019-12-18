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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  RX_CNTL_CSR ; 
 int /*<<< orphan*/  RX_CNTL_CSR_ENABLE_RX_DMA ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt61pci_init_bbp (struct rt2x00_dev*) ; 
 scalar_t__ rt61pci_init_queues (struct rt2x00_dev*) ; 
 scalar_t__ rt61pci_init_registers (struct rt2x00_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rt61pci_enable_radio(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;

	/*
	 * Initialize all registers.
	 */
	if (unlikely(rt61pci_init_queues(rt2x00dev) ||
		     rt61pci_init_registers(rt2x00dev) ||
		     rt61pci_init_bbp(rt2x00dev)))
		return -EIO;

	/*
	 * Enable RX.
	 */
	rt2x00mmio_register_read(rt2x00dev, RX_CNTL_CSR, &reg);
	rt2x00_set_field32(&reg, RX_CNTL_CSR_ENABLE_RX_DMA, 1);
	rt2x00mmio_register_write(rt2x00dev, RX_CNTL_CSR, reg);

	return 0;
}