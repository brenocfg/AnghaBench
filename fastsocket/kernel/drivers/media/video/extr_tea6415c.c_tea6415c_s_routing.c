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
typedef  int u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  debug ; 
 int i2c_smbus_write_byte (struct i2c_client*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,...) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tea6415c_s_routing(struct v4l2_subdev *sd,
			      u32 i, u32 o, u32 config)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	u8 byte = 0;
	int ret;

	v4l2_dbg(1, debug, sd, "i=%d, o=%d\n", i, o);

	/* check if the pins are valid */
	if (0 == ((1 == i ||  3 == i ||  5 == i ||  6 == i ||  8 == i || 10 == i || 20 == i || 11 == i)
	      && (18 == o || 17 == o || 16 == o || 15 == o || 14 == o || 13 == o)))
		return -EINVAL;

	/* to understand this, have a look at the tea6415c-specs (p.5) */
	switch (o) {
	case 18:
		byte = 0x00;
		break;
	case 14:
		byte = 0x20;
		break;
	case 16:
		byte = 0x10;
		break;
	case 17:
		byte = 0x08;
		break;
	case 15:
		byte = 0x18;
		break;
	case 13:
		byte = 0x28;
		break;
	};

	switch (i) {
	case 5:
		byte |= 0x00;
		break;
	case 8:
		byte |= 0x04;
		break;
	case 3:
		byte |= 0x02;
		break;
	case 20:
		byte |= 0x06;
		break;
	case 6:
		byte |= 0x01;
		break;
	case 10:
		byte |= 0x05;
		break;
	case 1:
		byte |= 0x03;
		break;
	case 11:
		byte |= 0x07;
		break;
	};

	ret = i2c_smbus_write_byte(client, byte);
	if (ret) {
		v4l2_dbg(1, debug, sd,
			"i2c_smbus_write_byte() failed, ret:%d\n", ret);
		return -EIO;
	}
	return ret;
}