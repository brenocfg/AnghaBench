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
typedef  int v4l2_std_id ;
typedef  scalar_t__ u8 ;
struct v4l2_subdev {int dummy; } ;
struct tvp5150 {int norm; } ;
struct TYPE_2__ {int vbi_type; } ;
struct i2c_vbi_ram_value {TYPE_1__ type; } ;

/* Variables and functions */
 scalar_t__ TVP5150_LINE_MODE_INI ; 
 int V4L2_STD_625_50 ; 
 int V4L2_STD_ALL ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 
 int tvp5150_read (struct v4l2_subdev*,scalar_t__) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int tvp5150_get_vbi(struct v4l2_subdev *sd,
			const struct i2c_vbi_ram_value *regs, int line)
{
	struct tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std = decoder->norm;
	u8 reg;
	int pos, type = 0;

	if (std == V4L2_STD_ALL) {
		v4l2_err(sd, "VBI can't be configured without knowing number of lines\n");
		return 0;
	} else if (std & V4L2_STD_625_50) {
		/* Don't follow NTSC Line number convension */
		line += 3;
	}

	if (line < 6 || line > 27)
		return 0;

	reg = ((line - 6) << 1) + TVP5150_LINE_MODE_INI;

	pos = tvp5150_read(sd, reg) & 0x0f;
	if (pos < 0x0f)
		type = regs[pos].type.vbi_type;

	pos = tvp5150_read(sd, reg + 1) & 0x0f;
	if (pos < 0x0f)
		type |= regs[pos].type.vbi_type;

	return type;
}