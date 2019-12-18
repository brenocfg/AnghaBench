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
#define  BRIDGE_OV511 129 
#define  BRIDGE_OV511PLUS 128 
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int R511_COMP_EN ; 
 int R511_COMP_LUT_EN ; 
 int R511_DRAM_FLOW_CTL ; 
 int R511_FIFO_OPTS ; 
 int /*<<< orphan*/  R51x_SYS_CUST_ID ; 
 int R51x_SYS_INIT ; 
 int R51x_SYS_RESET ; 
 int R51x_SYS_SNAP ; 
 int /*<<< orphan*/  ov51x_upload_quan_tables (struct sd*) ; 
 int /*<<< orphan*/  reg_r (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_regvals (struct sd*,struct ov_regvals const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov511_configure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* For 511 and 511+ */
	const struct ov_regvals init_511[] = {
		{ R51x_SYS_RESET,	0x7f },
		{ R51x_SYS_INIT,	0x01 },
		{ R51x_SYS_RESET,	0x7f },
		{ R51x_SYS_INIT,	0x01 },
		{ R51x_SYS_RESET,	0x3f },
		{ R51x_SYS_INIT,	0x01 },
		{ R51x_SYS_RESET,	0x3d },
	};

	const struct ov_regvals norm_511[] = {
		{ R511_DRAM_FLOW_CTL,	0x01 },
		{ R51x_SYS_SNAP,	0x00 },
		{ R51x_SYS_SNAP,	0x02 },
		{ R51x_SYS_SNAP,	0x00 },
		{ R511_FIFO_OPTS,	0x1f },
		{ R511_COMP_EN,		0x00 },
		{ R511_COMP_LUT_EN,	0x03 },
	};

	const struct ov_regvals norm_511_p[] = {
		{ R511_DRAM_FLOW_CTL,	0xff },
		{ R51x_SYS_SNAP,	0x00 },
		{ R51x_SYS_SNAP,	0x02 },
		{ R51x_SYS_SNAP,	0x00 },
		{ R511_FIFO_OPTS,	0xff },
		{ R511_COMP_EN,		0x00 },
		{ R511_COMP_LUT_EN,	0x03 },
	};

	const struct ov_regvals compress_511[] = {
		{ 0x70, 0x1f },
		{ 0x71, 0x05 },
		{ 0x72, 0x06 },
		{ 0x73, 0x06 },
		{ 0x74, 0x14 },
		{ 0x75, 0x03 },
		{ 0x76, 0x04 },
		{ 0x77, 0x04 },
	};

	PDEBUG(D_PROBE, "Device custom id %x", reg_r(sd, R51x_SYS_CUST_ID));

	write_regvals(sd, init_511, ARRAY_SIZE(init_511));

	switch (sd->bridge) {
	case BRIDGE_OV511:
		write_regvals(sd, norm_511, ARRAY_SIZE(norm_511));
		break;
	case BRIDGE_OV511PLUS:
		write_regvals(sd, norm_511_p, ARRAY_SIZE(norm_511_p));
		break;
	}

	/* Init compression */
	write_regvals(sd, compress_511, ARRAY_SIZE(compress_511));

	ov51x_upload_quan_tables(sd);
}