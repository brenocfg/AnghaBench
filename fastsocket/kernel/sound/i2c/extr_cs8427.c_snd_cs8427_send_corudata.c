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
struct snd_i2c_device {struct cs8427* private_data; } ;
struct TYPE_2__ {char* hw_udata; char* hw_status; } ;
struct cs8427 {int* regmap; TYPE_1__ playback; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int CS8427_EFTUI ; 
 char CS8427_REG_AUTOINC ; 
 char CS8427_REG_CORU_DATABUF ; 
 size_t CS8427_REG_UDATABUF ; 
 int CS8427_UBMMASK ; 
 int CS8427_UBMZEROS ; 
 int EIO ; 
 scalar_t__ memcmp (char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int snd_cs8427_reg_write (struct snd_i2c_device*,size_t,int) ; 
 int snd_cs8427_select_corudata (struct snd_i2c_device*,int) ; 
 int snd_i2c_sendbytes (struct snd_i2c_device*,char*,int) ; 
 char swapbits (unsigned char) ; 

__attribute__((used)) static int snd_cs8427_send_corudata(struct snd_i2c_device *device,
				    int udata,
				    unsigned char *ndata,
				    int count)
{
	struct cs8427 *chip = device->private_data;
	char *hw_data = udata ?
		chip->playback.hw_udata : chip->playback.hw_status;
	char data[32];
	int err, idx;

	if (!memcmp(hw_data, ndata, count))
		return 0;
	if ((err = snd_cs8427_select_corudata(device, udata)) < 0)
		return err;
	memcpy(hw_data, ndata, count);
	if (udata) {
		memset(data, 0, sizeof(data));
		if (memcmp(hw_data, data, count) == 0) {
			chip->regmap[CS8427_REG_UDATABUF] &= ~CS8427_UBMMASK;
			chip->regmap[CS8427_REG_UDATABUF] |= CS8427_UBMZEROS |
				CS8427_EFTUI;
			err = snd_cs8427_reg_write(device, CS8427_REG_UDATABUF,
						   chip->regmap[CS8427_REG_UDATABUF]);
			return err < 0 ? err : 0;
		}
	}
	data[0] = CS8427_REG_AUTOINC | CS8427_REG_CORU_DATABUF;
	for (idx = 0; idx < count; idx++)
		data[idx + 1] = swapbits(ndata[idx]);
	if (snd_i2c_sendbytes(device, data, count + 1) != count + 1)
		return -EIO;
	return 1;
}