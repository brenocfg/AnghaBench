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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int /*<<< orphan*/  command5_bits; int /*<<< orphan*/  (* write_byte ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ COMMAND5_REG ; 
 int /*<<< orphan*/  SCLOCK_BIT ; 
 int /*<<< orphan*/  SDATA_BIT ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void labpc_serial_out(struct comedi_device *dev, unsigned int value,
			     unsigned int value_width)
{
	int i;

	for (i = 1; i <= value_width; i++) {
		/*  clear serial clock */
		devpriv->command5_bits &= ~SCLOCK_BIT;
		/*  send bits most significant bit first */
		if (value & (1 << (value_width - i)))
			devpriv->command5_bits |= SDATA_BIT;
		else
			devpriv->command5_bits &= ~SDATA_BIT;
		udelay(1);
		devpriv->write_byte(devpriv->command5_bits,
				    dev->iobase + COMMAND5_REG);
		/*  set clock to load bit */
		devpriv->command5_bits |= SCLOCK_BIT;
		udelay(1);
		devpriv->write_byte(devpriv->command5_bits,
				    dev->iobase + COMMAND5_REG);
	}
}