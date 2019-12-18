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
struct sd {int brightness; int gain; int exposure; int /*<<< orphan*/  avg_lum; scalar_t__ autogain_ignore_frames; scalar_t__ sof_read; } ;
struct gspca_dev {int width; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/ * pac207_sensor_init ; 
 int /*<<< orphan*/  pac207_write_reg (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  pac207_write_regs (struct gspca_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 mode;

	pac207_write_reg(gspca_dev, 0x0f, 0x10); /* Power control (Bit 6-0) */
	pac207_write_regs(gspca_dev, 0x0002, pac207_sensor_init[0], 8);
	pac207_write_regs(gspca_dev, 0x000a, pac207_sensor_init[1], 8);
	pac207_write_regs(gspca_dev, 0x0012, pac207_sensor_init[2], 8);
	pac207_write_regs(gspca_dev, 0x0042, pac207_sensor_init[3], 8);

	/* Compression Balance */
	if (gspca_dev->width == 176)
		pac207_write_reg(gspca_dev, 0x4a, 0xff);
	else
		pac207_write_reg(gspca_dev, 0x4a, 0x30);
	pac207_write_reg(gspca_dev, 0x4b, 0x00); /* Sram test value */
	pac207_write_reg(gspca_dev, 0x08, sd->brightness);

	/* PGA global gain (Bit 4-0) */
	pac207_write_reg(gspca_dev, 0x0e, sd->gain);
	pac207_write_reg(gspca_dev, 0x02, sd->exposure); /* PXCK = 12MHz /n */

	mode = 0x02; /* Image Format (Bit 0), LED (1), Compr. test mode (2) */
	if (gspca_dev->width == 176) {	/* 176x144 */
		mode |= 0x01;
		PDEBUG(D_STREAM, "pac207_start mode 176x144");
	} else {				/* 352x288 */
		PDEBUG(D_STREAM, "pac207_start mode 352x288");
	}
	pac207_write_reg(gspca_dev, 0x41, mode);

	pac207_write_reg(gspca_dev, 0x13, 0x01); /* Bit 0, auto clear */
	pac207_write_reg(gspca_dev, 0x1c, 0x01); /* not documented */
	msleep(10);
	pac207_write_reg(gspca_dev, 0x40, 0x01); /* Start ISO pipe */

	sd->sof_read = 0;
	sd->autogain_ignore_frames = 0;
	atomic_set(&sd->avg_lum, -1);
	return 0;
}