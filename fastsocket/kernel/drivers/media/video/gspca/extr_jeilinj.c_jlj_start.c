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
typedef  int u8 ;
struct TYPE_2__ {int member_0; int member_1; } ;
struct jlj_command {int member_1; scalar_t__ ack_wanted; int /*<<< orphan*/  instruction; TYPE_1__ member_0; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct jlj_command*) ; 
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int jlj_read1 (struct gspca_dev*,int) ; 
 int jlj_write2 (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jlj_start(struct gspca_dev *gspca_dev)
{
	int i;
	int retval = -1;
	u8 response = 0xff;
	struct jlj_command start_commands[] = {
		{{0x71, 0x81}, 0},
		{{0x70, 0x05}, 0},
		{{0x95, 0x70}, 1},
		{{0x71, 0x81}, 0},
		{{0x70, 0x04}, 0},
		{{0x95, 0x70}, 1},
		{{0x71, 0x00}, 0},
		{{0x70, 0x08}, 0},
		{{0x95, 0x70}, 1},
		{{0x94, 0x02}, 0},
		{{0xde, 0x24}, 0},
		{{0x94, 0x02}, 0},
		{{0xdd, 0xf0}, 0},
		{{0x94, 0x02}, 0},
		{{0xe3, 0x2c}, 0},
		{{0x94, 0x02}, 0},
		{{0xe4, 0x00}, 0},
		{{0x94, 0x02}, 0},
		{{0xe5, 0x00}, 0},
		{{0x94, 0x02}, 0},
		{{0xe6, 0x2c}, 0},
		{{0x94, 0x03}, 0},
		{{0xaa, 0x00}, 0},
		{{0x71, 0x1e}, 0},
		{{0x70, 0x06}, 0},
		{{0x71, 0x80}, 0},
		{{0x70, 0x07}, 0}
	};
	for (i = 0; i < ARRAY_SIZE(start_commands); i++) {
		retval = jlj_write2(gspca_dev, start_commands[i].instruction);
		if (retval < 0)
			return retval;
		if (start_commands[i].ack_wanted)
			retval = jlj_read1(gspca_dev, response);
		if (retval < 0)
			return retval;
	}
	PDEBUG(D_ERR, "jlj_start retval is %d", retval);
	return retval;
}