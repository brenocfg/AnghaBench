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
struct TYPE_2__ {struct axon_ram_bank* platform_data; } ;
struct of_device {TYPE_1__ dev; } ;
struct axon_ram_bank {int /*<<< orphan*/  ecc_counter; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 

__attribute__((used)) static irqreturn_t
axon_ram_irq_handler(int irq, void *dev)
{
	struct of_device *device = dev;
	struct axon_ram_bank *bank = device->dev.platform_data;

	BUG_ON(!bank);

	dev_err(&device->dev, "Correctable memory error occured\n");
	bank->ecc_counter++;
	return IRQ_HANDLED;
}