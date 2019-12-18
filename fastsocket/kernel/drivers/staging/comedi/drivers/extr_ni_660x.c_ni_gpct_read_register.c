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
struct ni_gpct {int /*<<< orphan*/  chip_index; TYPE_1__* counter_dev; } ;
struct comedi_device {int dummy; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;
typedef  enum NI_660x_Register { ____Placeholder_NI_660x_Register } NI_660x_Register ;
struct TYPE_2__ {struct comedi_device* dev; } ;

/* Variables and functions */
 int ni_660x_read_register (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int ni_gpct_to_660x_register (int) ; 

__attribute__((used)) static unsigned ni_gpct_read_register(struct ni_gpct *counter,
				      enum ni_gpct_register reg)
{
	struct comedi_device *dev = counter->counter_dev->dev;
	enum NI_660x_Register ni_660x_register = ni_gpct_to_660x_register(reg);
	return ni_660x_read_register(dev, counter->chip_index,
				     ni_660x_register);
}