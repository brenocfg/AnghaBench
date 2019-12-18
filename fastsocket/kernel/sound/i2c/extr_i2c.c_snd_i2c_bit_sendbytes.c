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
struct snd_i2c_device {int flags; int addr; struct snd_i2c_bus* bus; } ;
struct snd_i2c_bus {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int SND_I2C_DEVICE_ADDRTEN ; 
 int /*<<< orphan*/  snd_i2c_bit_hw_stop (struct snd_i2c_bus*) ; 
 int snd_i2c_bit_sendbyte (struct snd_i2c_bus*,int) ; 
 int /*<<< orphan*/  snd_i2c_bit_start (struct snd_i2c_bus*) ; 
 int /*<<< orphan*/  snd_i2c_bit_stop (struct snd_i2c_bus*) ; 

__attribute__((used)) static int snd_i2c_bit_sendbytes(struct snd_i2c_device *device,
				 unsigned char *bytes, int count)
{
	struct snd_i2c_bus *bus = device->bus;
	int err, res = 0;

	if (device->flags & SND_I2C_DEVICE_ADDRTEN)
		return -EIO;		/* not yet implemented */
	snd_i2c_bit_start(bus);
	if ((err = snd_i2c_bit_sendbyte(bus, device->addr << 1)) < 0) {
		snd_i2c_bit_hw_stop(bus);
		return err;
	}
	while (count-- > 0) {
		if ((err = snd_i2c_bit_sendbyte(bus, *bytes++)) < 0) {
			snd_i2c_bit_hw_stop(bus);
			return err;
		}
		res++;
	}
	snd_i2c_bit_stop(bus);
	return res;
}