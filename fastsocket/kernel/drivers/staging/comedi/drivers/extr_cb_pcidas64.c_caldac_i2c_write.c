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
 int CALDAC0_I2C_ADDR ; 
 int CALDAC1_I2C_ADDR ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  i2c_write (struct comedi_device*,int,int*,int) ; 

__attribute__((used)) static int caldac_i2c_write(struct comedi_device *dev,
			    unsigned int caldac_channel, unsigned int value)
{
	uint8_t serial_bytes[3];
	uint8_t i2c_addr;
	enum pointer_bits {
		/*  manual has gain and offset bits switched */
		OFFSET_0_2 = 0x1,
		GAIN_0_2 = 0x2,
		OFFSET_1_3 = 0x4,
		GAIN_1_3 = 0x8,
	};
	enum data_bits {
		NOT_CLEAR_REGISTERS = 0x20,
	};

	switch (caldac_channel) {
	case 0:		/*  chan 0 offset */
		i2c_addr = CALDAC0_I2C_ADDR;
		serial_bytes[0] = OFFSET_0_2;
		break;
	case 1:		/*  chan 1 offset */
		i2c_addr = CALDAC0_I2C_ADDR;
		serial_bytes[0] = OFFSET_1_3;
		break;
	case 2:		/*  chan 2 offset */
		i2c_addr = CALDAC1_I2C_ADDR;
		serial_bytes[0] = OFFSET_0_2;
		break;
	case 3:		/*  chan 3 offset */
		i2c_addr = CALDAC1_I2C_ADDR;
		serial_bytes[0] = OFFSET_1_3;
		break;
	case 4:		/*  chan 0 gain */
		i2c_addr = CALDAC0_I2C_ADDR;
		serial_bytes[0] = GAIN_0_2;
		break;
	case 5:		/*  chan 1 gain */
		i2c_addr = CALDAC0_I2C_ADDR;
		serial_bytes[0] = GAIN_1_3;
		break;
	case 6:		/*  chan 2 gain */
		i2c_addr = CALDAC1_I2C_ADDR;
		serial_bytes[0] = GAIN_0_2;
		break;
	case 7:		/*  chan 3 gain */
		i2c_addr = CALDAC1_I2C_ADDR;
		serial_bytes[0] = GAIN_1_3;
		break;
	default:
		comedi_error(dev, "invalid caldac channel\n");
		return -1;
		break;
	}
	serial_bytes[1] = NOT_CLEAR_REGISTERS | ((value >> 8) & 0xf);
	serial_bytes[2] = value & 0xff;
	i2c_write(dev, i2c_addr, serial_bytes, 3);
	return 0;
}