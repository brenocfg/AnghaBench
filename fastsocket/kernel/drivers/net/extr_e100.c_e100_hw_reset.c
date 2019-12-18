#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nic {TYPE_1__* csr; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  e100_disable_irq (struct nic*) ; 
 int /*<<< orphan*/  e100_write_flush (struct nic*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selective_reset ; 
 int /*<<< orphan*/  software_reset ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void e100_hw_reset(struct nic *nic)
{
	/* Put CU and RU into idle with a selective reset to get
	 * device off of PCI bus */
	iowrite32(selective_reset, &nic->csr->port);
	e100_write_flush(nic); udelay(20);

	/* Now fully reset device */
	iowrite32(software_reset, &nic->csr->port);
	e100_write_flush(nic); udelay(20);

	/* Mask off our interrupt line - it's unmasked after reset */
	e100_disable_irq(nic);
}