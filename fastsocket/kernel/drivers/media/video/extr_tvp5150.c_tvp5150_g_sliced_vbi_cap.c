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
typedef  scalar_t__ u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_sliced_vbi_cap {int /*<<< orphan*/  service_set; int /*<<< orphan*/ ** service_lines; } ;
struct TYPE_2__ {int ini_line; int end_line; int /*<<< orphan*/  vbi_type; } ;
struct i2c_vbi_ram_value {scalar_t__ reg; TYPE_1__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memset (struct v4l2_sliced_vbi_cap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 
 struct i2c_vbi_ram_value* vbi_ram_default ; 

__attribute__((used)) static int tvp5150_g_sliced_vbi_cap(struct v4l2_subdev *sd,
				struct v4l2_sliced_vbi_cap *cap)
{
	const struct i2c_vbi_ram_value *regs = vbi_ram_default;
	int line;

	v4l2_dbg(1, debug, sd, "g_sliced_vbi_cap\n");
	memset(cap, 0, sizeof *cap);

	while (regs->reg != (u16)-1 ) {
		for (line=regs->type.ini_line;line<=regs->type.end_line;line++) {
			cap->service_lines[0][line] |= regs->type.vbi_type;
		}
		cap->service_set |= regs->type.vbi_type;

		regs++;
	}
	return 0;
}