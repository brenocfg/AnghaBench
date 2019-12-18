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
typedef  int uint8_t ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT (char*,int) ; 
 int /*<<< orphan*/  i2c_set_scl (struct comedi_device*,int) ; 
 int /*<<< orphan*/  i2c_set_sda (struct comedi_device*,int) ; 

__attribute__((used)) static void i2c_write_byte(struct comedi_device *dev, uint8_t byte)
{
	uint8_t bit;
	unsigned int num_bits = 8;

	DEBUG_PRINT("writing to i2c byte 0x%x\n", byte);

	for (bit = 1 << (num_bits - 1); bit; bit >>= 1) {
		i2c_set_scl(dev, 0);
		if ((byte & bit))
			i2c_set_sda(dev, 1);
		else
			i2c_set_sda(dev, 0);
		i2c_set_scl(dev, 1);
	}
}