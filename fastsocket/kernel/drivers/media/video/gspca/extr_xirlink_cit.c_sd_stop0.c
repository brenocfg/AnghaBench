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
struct sd {int model; scalar_t__ button_state; } ;
struct gspca_dev {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CIT_IBM_NETCAM_PRO 133 
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int /*<<< orphan*/  KEY_CAMERA ; 
 int /*<<< orphan*/  cit_model2_Packet1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  cit_model3_Packet1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  cit_read_reg (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cit_send_FF_04_02 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_write_reg (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_stop0(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* We cannot use gspca_dev->present here as that is not set when
	   sd_init gets called and we get called from sd_init */
	if (!gspca_dev->dev)
		return;

	switch (sd->model) {
	case CIT_MODEL0:
		/* HDG windows does this, but it causes the cams autogain to
		   restart from a gain of 0, which does not look good when
		   changing resolutions. */
		/* cit_write_reg(gspca_dev, 0x0000, 0x0112); */
		cit_write_reg(gspca_dev, 0x00c0, 0x0100); /* LED Off */
		break;
	case CIT_MODEL1:
		cit_send_FF_04_02(gspca_dev);
		cit_read_reg(gspca_dev, 0x0100, 0);
		cit_write_reg(gspca_dev, 0x81, 0x0100);	/* LED Off */
		break;
	case CIT_MODEL2:
	case CIT_MODEL4:
		cit_model2_Packet1(gspca_dev, 0x0030, 0x0004);

		cit_write_reg(gspca_dev, 0x0080, 0x0100);	/* LED Off */
		cit_write_reg(gspca_dev, 0x0020, 0x0111);
		cit_write_reg(gspca_dev, 0x00a0, 0x0111);

		cit_model2_Packet1(gspca_dev, 0x0030, 0x0002);

		cit_write_reg(gspca_dev, 0x0020, 0x0111);
		cit_write_reg(gspca_dev, 0x0000, 0x0112);
		break;
	case CIT_MODEL3:
		cit_write_reg(gspca_dev, 0x0006, 0x012c);
		cit_model3_Packet1(gspca_dev, 0x0046, 0x0000);
		cit_read_reg(gspca_dev, 0x0116, 0);
		cit_write_reg(gspca_dev, 0x0064, 0x0116);
		cit_read_reg(gspca_dev, 0x0115, 0);
		cit_write_reg(gspca_dev, 0x0003, 0x0115);
		cit_write_reg(gspca_dev, 0x0008, 0x0123);
		cit_write_reg(gspca_dev, 0x0000, 0x0117);
		cit_write_reg(gspca_dev, 0x0000, 0x0112);
		cit_write_reg(gspca_dev, 0x0080, 0x0100);
		break;
	case CIT_IBM_NETCAM_PRO:
		cit_model3_Packet1(gspca_dev, 0x0049, 0x00ff);
		cit_write_reg(gspca_dev, 0x0006, 0x012c);
		cit_write_reg(gspca_dev, 0x0000, 0x0116);
		/* HDG windows does this, but I cannot get the camera
		   to restart with this without redoing the entire init
		   sequence which makes switching modes really slow */
		/* cit_write_reg(gspca_dev, 0x0006, 0x0115); */
		cit_write_reg(gspca_dev, 0x0008, 0x0123);
		cit_write_reg(gspca_dev, 0x0000, 0x0117);
		cit_write_reg(gspca_dev, 0x0003, 0x0133);
		cit_write_reg(gspca_dev, 0x0000, 0x0111);
		/* HDG windows does this, but I get a green picture when
		   restarting the stream after this */
		/* cit_write_reg(gspca_dev, 0x0000, 0x0112); */
		cit_write_reg(gspca_dev, 0x00c0, 0x0100);
		break;
	}

#if defined(CONFIG_INPUT) || defined(CONFIG_INPUT_MODULE)
	/* If the last button state is pressed, release it now! */
	if (sd->button_state) {
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
		sd->button_state = 0;
	}
#endif
}