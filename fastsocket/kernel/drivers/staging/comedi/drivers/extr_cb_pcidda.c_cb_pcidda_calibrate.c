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
struct TYPE_2__ {unsigned int* ao_range; int /*<<< orphan*/ * eeprom_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  caldac_number (unsigned int) ; 
 int /*<<< orphan*/  cb_pcidda_write_caldac (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  coarse_gain_channel (unsigned int) ; 
 int /*<<< orphan*/  coarse_offset_channel (unsigned int) ; 
 TYPE_1__* devpriv ; 
 unsigned int eeprom_coarse_byte (int /*<<< orphan*/ ) ; 
 unsigned int eeprom_fine_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fine_gain_channel (unsigned int) ; 
 int /*<<< orphan*/  fine_offset_channel (unsigned int) ; 
 size_t gain_eeprom_address (unsigned int,unsigned int) ; 
 size_t offset_eeprom_address (unsigned int,unsigned int) ; 

__attribute__((used)) static void cb_pcidda_calibrate(struct comedi_device *dev, unsigned int channel,
				unsigned int range)
{
	unsigned int coarse_offset, fine_offset, coarse_gain, fine_gain;

	/*  remember range so we can tell when we need to readjust calibration */
	devpriv->ao_range[channel] = range;

	/*  get values from eeprom data */
	coarse_offset =
	    eeprom_coarse_byte(devpriv->eeprom_data
			       [offset_eeprom_address(channel, range)]);
	fine_offset =
	    eeprom_fine_byte(devpriv->eeprom_data
			     [offset_eeprom_address(channel, range)]);
	coarse_gain =
	    eeprom_coarse_byte(devpriv->eeprom_data
			       [gain_eeprom_address(channel, range)]);
	fine_gain =
	    eeprom_fine_byte(devpriv->eeprom_data
			     [gain_eeprom_address(channel, range)]);

	/*  set caldacs */
	cb_pcidda_write_caldac(dev, caldac_number(channel),
			       coarse_offset_channel(channel), coarse_offset);
	cb_pcidda_write_caldac(dev, caldac_number(channel),
			       fine_offset_channel(channel), fine_offset);
	cb_pcidda_write_caldac(dev, caldac_number(channel),
			       coarse_gain_channel(channel), coarse_gain);
	cb_pcidda_write_caldac(dev, caldac_number(channel),
			       fine_gain_channel(channel), fine_gain);
}