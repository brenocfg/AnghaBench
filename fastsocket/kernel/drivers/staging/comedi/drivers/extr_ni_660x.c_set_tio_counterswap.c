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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClockConfigRegister ; 
 int /*<<< orphan*/  CounterSwap ; 
 int /*<<< orphan*/  ni_660x_write_register (struct comedi_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_tio_counterswap(struct comedi_device *dev, int chipset)
{
	/* See P. 3.5 of the Register-Level Programming manual.  The
	   CounterSwap bit has to be set on the second chip, otherwise
	   it will try to use the same pins as the first chip.
	 */
	if (chipset)
		ni_660x_write_register(dev, chipset, CounterSwap,
				       ClockConfigRegister);
	else
		ni_660x_write_register(dev, chipset, 0, ClockConfigRegister);
}