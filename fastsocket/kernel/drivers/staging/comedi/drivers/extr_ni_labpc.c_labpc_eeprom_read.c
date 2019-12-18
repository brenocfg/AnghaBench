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
struct TYPE_2__ {int command5_bits; int /*<<< orphan*/  (* write_byte ) (int,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ COMMAND5_REG ; 
 int EEPROM_EN_BIT ; 
 int EEPROM_WRITE_UNPROTECT_BIT ; 
 TYPE_1__* devpriv ; 
 unsigned int labpc_serial_in (struct comedi_device*) ; 
 int /*<<< orphan*/  labpc_serial_out (struct comedi_device*,int const,int const) ; 
 int /*<<< orphan*/  stub1 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int labpc_eeprom_read(struct comedi_device *dev,
				      unsigned int address)
{
	unsigned int value;
	const int read_instruction = 0x3;	/*  bits to tell eeprom to expect a read */
	const int write_length = 8;	/*  8 bit write lengths to eeprom */

	/*  enable read/write to eeprom */
	devpriv->command5_bits &= ~EEPROM_EN_BIT;
	udelay(1);
	devpriv->write_byte(devpriv->command5_bits, dev->iobase + COMMAND5_REG);
	devpriv->command5_bits |= EEPROM_EN_BIT | EEPROM_WRITE_UNPROTECT_BIT;
	udelay(1);
	devpriv->write_byte(devpriv->command5_bits, dev->iobase + COMMAND5_REG);

	/*  send read instruction */
	labpc_serial_out(dev, read_instruction, write_length);
	/*  send 8 bit address to read from */
	labpc_serial_out(dev, address, write_length);
	/*  read result */
	value = labpc_serial_in(dev);

	/*  disable read/write to eeprom */
	devpriv->command5_bits &= ~EEPROM_EN_BIT & ~EEPROM_WRITE_UNPROTECT_BIT;
	udelay(1);
	devpriv->write_byte(devpriv->command5_bits, dev->iobase + COMMAND5_REG);

	return value;
}