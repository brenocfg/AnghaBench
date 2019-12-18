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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct v4l2_subdev {int dummy; } ;
struct tvp5150 {int norm; } ;
struct TYPE_2__ {unsigned int vbi_type; int ini_line; int end_line; } ;
struct i2c_vbi_ram_value {scalar_t__ reg; TYPE_1__ type; } ;

/* Variables and functions */
 int TVP5150_LINE_MODE_INI ; 
 int V4L2_STD_625_50 ; 
 int V4L2_STD_ALL ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_write (struct v4l2_subdev*,int,unsigned int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int tvp5150_set_vbi(struct v4l2_subdev *sd,
			const struct i2c_vbi_ram_value *regs,
			unsigned int type,u8 flags, int line,
			const int fields)
{
	struct tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std = decoder->norm;
	u8 reg;
	int pos=0;

	if (std == V4L2_STD_ALL) {
		v4l2_err(sd, "VBI can't be configured without knowing number of lines\n");
		return 0;
	} else if (std & V4L2_STD_625_50) {
		/* Don't follow NTSC Line number convension */
		line += 3;
	}

	if (line<6||line>27)
		return 0;

	while (regs->reg != (u16)-1 ) {
		if ((type & regs->type.vbi_type) &&
		    (line>=regs->type.ini_line) &&
		    (line<=regs->type.end_line)) {
			type=regs->type.vbi_type;
			break;
		}

		regs++;
		pos++;
	}
	if (regs->reg == (u16)-1)
		return 0;

	type=pos | (flags & 0xf0);
	reg=((line-6)<<1)+TVP5150_LINE_MODE_INI;

	if (fields&1) {
		tvp5150_write(sd, reg, type);
	}

	if (fields&2) {
		tvp5150_write(sd, reg+1, type);
	}

	return type;
}