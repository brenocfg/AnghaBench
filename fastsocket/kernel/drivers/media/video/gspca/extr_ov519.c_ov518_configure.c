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
struct sd {int bridge; } ;
struct ov_regvals {int member_0; int member_1; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ov_regvals const*) ; 
#define  BRIDGE_OV518 129 
#define  BRIDGE_OV518PLUS 128 
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  R518_GPIO_CTL ; 
 int /*<<< orphan*/  R51x_SYS_CUST_ID ; 
 int R51x_SYS_INIT ; 
 int R51x_SYS_RESET ; 
 int R51x_SYS_SNAP ; 
 int /*<<< orphan*/  ov51x_upload_quan_tables (struct sd*) ; 
 int reg_r (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int,int) ; 
 int /*<<< orphan*/  reg_w_mask (struct sd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  write_regvals (struct sd*,struct ov_regvals const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov518_configure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* For 518 and 518+ */
	const struct ov_regvals init_518[] = {
		{ R51x_SYS_RESET,	0x40 },
		{ R51x_SYS_INIT,	0xe1 },
		{ R51x_SYS_RESET,	0x3e },
		{ R51x_SYS_INIT,	0xe1 },
		{ R51x_SYS_RESET,	0x00 },
		{ R51x_SYS_INIT,	0xe1 },
		{ 0x46,			0x00 },
		{ 0x5d,			0x03 },
	};

	const struct ov_regvals norm_518[] = {
		{ R51x_SYS_SNAP,	0x02 }, /* Reset */
		{ R51x_SYS_SNAP,	0x01 }, /* Enable */
		{ 0x31,			0x0f },
		{ 0x5d,			0x03 },
		{ 0x24,			0x9f },
		{ 0x25,			0x90 },
		{ 0x20,			0x00 },
		{ 0x51,			0x04 },
		{ 0x71,			0x19 },
		{ 0x2f,			0x80 },
	};

	const struct ov_regvals norm_518_p[] = {
		{ R51x_SYS_SNAP,	0x02 }, /* Reset */
		{ R51x_SYS_SNAP,	0x01 }, /* Enable */
		{ 0x31,			0x0f },
		{ 0x5d,			0x03 },
		{ 0x24,			0x9f },
		{ 0x25,			0x90 },
		{ 0x20,			0x60 },
		{ 0x51,			0x02 },
		{ 0x71,			0x19 },
		{ 0x40,			0xff },
		{ 0x41,			0x42 },
		{ 0x46,			0x00 },
		{ 0x33,			0x04 },
		{ 0x21,			0x19 },
		{ 0x3f,			0x10 },
		{ 0x2f,			0x80 },
	};

	/* First 5 bits of custom ID reg are a revision ID on OV518 */
	PDEBUG(D_PROBE, "Device revision %d",
		0x1f & reg_r(sd, R51x_SYS_CUST_ID));

	write_regvals(sd, init_518, ARRAY_SIZE(init_518));

	/* Set LED GPIO pin to output mode */
	reg_w_mask(sd, R518_GPIO_CTL, 0x00, 0x02);

	switch (sd->bridge) {
	case BRIDGE_OV518:
		write_regvals(sd, norm_518, ARRAY_SIZE(norm_518));
		break;
	case BRIDGE_OV518PLUS:
		write_regvals(sd, norm_518_p, ARRAY_SIZE(norm_518_p));
		break;
	}

	ov51x_upload_quan_tables(sd);

	reg_w(sd, 0x2f, 0x80);
}