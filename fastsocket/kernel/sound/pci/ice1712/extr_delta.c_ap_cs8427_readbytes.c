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
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; } ;
struct snd_i2c_device {int addr; TYPE_1__* bus; } ;
struct TYPE_2__ {struct snd_ice1712* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_cs8427_codec_deassert (struct snd_ice1712*,unsigned char) ; 
 unsigned char ap_cs8427_codec_select (struct snd_ice1712*) ; 
 int /*<<< orphan*/  ap_cs8427_read_byte (struct snd_ice1712*,unsigned char) ; 
 int /*<<< orphan*/  ap_cs8427_write_byte (struct snd_ice1712*,int,unsigned char) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ap_cs8427_readbytes(struct snd_i2c_device *device, unsigned char *bytes, int count)
{
	struct snd_ice1712 *ice = device->bus->private_data;
	int res = count;
	unsigned char tmp;
	
	mutex_lock(&ice->gpio_mutex);
	tmp = ap_cs8427_codec_select(ice);
	ap_cs8427_write_byte(ice, (device->addr << 1) | 1, tmp); /* address + read mode */
	while (count-- > 0)
		*bytes++ = ap_cs8427_read_byte(ice, tmp);
	ap_cs8427_codec_deassert(ice, tmp);
	mutex_unlock(&ice->gpio_mutex);
	return res;
}