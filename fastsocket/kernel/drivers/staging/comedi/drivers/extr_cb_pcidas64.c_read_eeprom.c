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
typedef  int const uint8_t ;
typedef  unsigned int uint16_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {void* plx9080_iobase; int plx_control_bits; } ;

/* Variables and functions */
 int CTL_EE_CLK ; 
 int CTL_EE_CS ; 
 int CTL_EE_R ; 
 int CTL_EE_W ; 
 int CTL_USERO ; 
 int PLX_CONTROL_REG ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int readl (void* const) ; 
 int /*<<< orphan*/  udelay (int const) ; 
 int /*<<< orphan*/  writel (int,void* const) ; 

__attribute__((used)) static uint16_t read_eeprom(struct comedi_device *dev, uint8_t address)
{
	static const int bitstream_length = 11;
	static const int read_command = 0x6;
	unsigned int bitstream = (read_command << 8) | address;
	unsigned int bit;
	void *const plx_control_addr =
	    priv(dev)->plx9080_iobase + PLX_CONTROL_REG;
	uint16_t value;
	static const int value_length = 16;
	static const int eeprom_udelay = 1;

	udelay(eeprom_udelay);
	priv(dev)->plx_control_bits &= ~CTL_EE_CLK & ~CTL_EE_CS;
	/*  make sure we don't send anything to the i2c bus on 4020 */
	priv(dev)->plx_control_bits |= CTL_USERO;
	writel(priv(dev)->plx_control_bits, plx_control_addr);
	/*  activate serial eeprom */
	udelay(eeprom_udelay);
	priv(dev)->plx_control_bits |= CTL_EE_CS;
	writel(priv(dev)->plx_control_bits, plx_control_addr);

	/*  write read command and desired memory address */
	for (bit = 1 << (bitstream_length - 1); bit; bit >>= 1) {
		/*  set bit to be written */
		udelay(eeprom_udelay);
		if (bitstream & bit)
			priv(dev)->plx_control_bits |= CTL_EE_W;
		else
			priv(dev)->plx_control_bits &= ~CTL_EE_W;
		writel(priv(dev)->plx_control_bits, plx_control_addr);
		/*  clock in bit */
		udelay(eeprom_udelay);
		priv(dev)->plx_control_bits |= CTL_EE_CLK;
		writel(priv(dev)->plx_control_bits, plx_control_addr);
		udelay(eeprom_udelay);
		priv(dev)->plx_control_bits &= ~CTL_EE_CLK;
		writel(priv(dev)->plx_control_bits, plx_control_addr);
	}
	/*  read back value from eeprom memory location */
	value = 0;
	for (bit = 1 << (value_length - 1); bit; bit >>= 1) {
		/*  clock out bit */
		udelay(eeprom_udelay);
		priv(dev)->plx_control_bits |= CTL_EE_CLK;
		writel(priv(dev)->plx_control_bits, plx_control_addr);
		udelay(eeprom_udelay);
		priv(dev)->plx_control_bits &= ~CTL_EE_CLK;
		writel(priv(dev)->plx_control_bits, plx_control_addr);
		udelay(eeprom_udelay);
		if (readl(plx_control_addr) & CTL_EE_R)
			value |= bit;
	}

	/*  deactivate eeprom serial input */
	udelay(eeprom_udelay);
	priv(dev)->plx_control_bits &= ~CTL_EE_CS;
	writel(priv(dev)->plx_control_bits, plx_control_addr);

	return value;
}