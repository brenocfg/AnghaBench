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
typedef  scalar_t__ u8 ;
struct v4l2_subdev {int dummy; } ;
struct saa7110 {scalar_t__ reg; } ;
struct i2c_client {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ SAA7110_NR_REG ; 
 scalar_t__ i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_master_send (struct i2c_client*,scalar_t__ const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__ const*,unsigned int) ; 
 int saa7110_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct saa7110* to_saa7110 (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa7110_write_block(struct v4l2_subdev *sd, const u8 *data, unsigned int len)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct saa7110 *decoder = to_saa7110(sd);
	int ret = -1;
	u8 reg = *data;		/* first register to write to */

	/* Sanity check */
	if (reg + (len - 1) > SAA7110_NR_REG)
		return ret;

	/* the saa7110 has an autoincrement function, use it if
	 * the adapter understands raw I2C */
	if (i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		ret = i2c_master_send(client, data, len);

		/* Cache the written data */
		memcpy(decoder->reg + reg, data + 1, len - 1);
	} else {
		for (++data, --len; len; len--) {
			ret = saa7110_write(sd, reg++, *data++);
			if (ret < 0)
				break;
		}
	}

	return ret;
}