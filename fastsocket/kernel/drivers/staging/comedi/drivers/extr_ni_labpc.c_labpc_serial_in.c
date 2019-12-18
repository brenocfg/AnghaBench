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
struct TYPE_2__ {int status2_bits; int (* read_byte ) (scalar_t__) ;int /*<<< orphan*/  command5_bits; int /*<<< orphan*/  (* write_byte ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ COMMAND5_REG ; 
 int EEPROM_OUT_BIT ; 
 int /*<<< orphan*/  SCLOCK_BIT ; 
 scalar_t__ STATUS2_REG ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int stub3 (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int labpc_serial_in(struct comedi_device *dev)
{
	unsigned int value = 0;
	int i;
	const int value_width = 8;	/*  number of bits wide values are */

	for (i = 1; i <= value_width; i++) {
		/*  set serial clock */
		devpriv->command5_bits |= SCLOCK_BIT;
		udelay(1);
		devpriv->write_byte(devpriv->command5_bits,
				    dev->iobase + COMMAND5_REG);
		/*  clear clock bit */
		devpriv->command5_bits &= ~SCLOCK_BIT;
		udelay(1);
		devpriv->write_byte(devpriv->command5_bits,
				    dev->iobase + COMMAND5_REG);
		/*  read bits most significant bit first */
		udelay(1);
		devpriv->status2_bits =
		    devpriv->read_byte(dev->iobase + STATUS2_REG);
		if (devpriv->status2_bits & EEPROM_OUT_BIT) {
			value |= 1 << (value_width - i);
		}
	}

	return value;
}