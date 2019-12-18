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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ timer_divisor_2; scalar_t__ timer_divisor_1; int /*<<< orphan*/  lcr_io_base; } ;

/* Variables and functions */
 TYPE_1__* dev_private ; 
 int /*<<< orphan*/  pci9111_autoscan_set (struct comedi_device*,int) ; 
 int /*<<< orphan*/  pci9111_pretrigger_set (struct comedi_device*,int) ; 
 int /*<<< orphan*/  pci9111_timer_set (struct comedi_device*) ; 
 int /*<<< orphan*/  pci9111_trigger_source_set (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plx9050_interrupt_control (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  software ; 

__attribute__((used)) static int pci9111_reset(struct comedi_device *dev)
{
	/*  Set trigger source to software */

	plx9050_interrupt_control(dev_private->lcr_io_base, true, true, true,
				  true, false);

	pci9111_trigger_source_set(dev, software);
	pci9111_pretrigger_set(dev, false);
	pci9111_autoscan_set(dev, false);

	/*  Reset 8254 chip */

	dev_private->timer_divisor_1 = 0;
	dev_private->timer_divisor_2 = 0;

	pci9111_timer_set(dev);

	return 0;
}