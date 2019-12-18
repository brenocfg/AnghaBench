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
struct sd {int subtype; int /*<<< orphan*/  quality; int /*<<< orphan*/  jpeg_hdr; } ;
struct gspca_dev {int* usb_buf; int /*<<< orphan*/  curr_mode; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
typedef  int __u8 ;

/* Variables and functions */
#define  AgfaCl20 142 
#define  AiptekPocketDV 141 
#define  BenqDC1016 140 
 int /*<<< orphan*/  Clicksmart510_defaults ; 
#define  CreativePCCam300 139 
#define  DLinkDSC350 138 
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  D_STREAM ; 
#define  Gsmartmini 137 
#define  IntelPocketPCCamera 136 
#define  KodakEZ200 135 
#define  LogitechClickSmart310 134 
#define  LogitechClickSmart510 133 
#define  LogitechTraveler 132 
#define  MustekGsmart300 131 
#define  Optimedia 130 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
#define  PalmPixDC85 129 
#define  ToptroIndus 128 
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qtable_creative_pccam ; 
 int /*<<< orphan*/  qtable_kodak_ez200 ; 
 int /*<<< orphan*/  qtable_pocketdv ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_r_wait (struct gspca_dev*,int /*<<< orphan*/ ,int,int) ; 
 int reg_w (struct gspca_dev*,int,int,int) ; 
 int spca500_full_reset (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca500_reinit (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca500_setmode (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  spca500_synch310 (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca500_visual_defaults ; 
 int spca50x_setup_qtable (struct gspca_dev*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_vector (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int err;
	__u8 Data;
	__u8 xmult, ymult;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->height, gspca_dev->width,
			0x22);		/* JPEG 411 */
	jpeg_set_qual(sd->jpeg_hdr, sd->quality);

	if (sd->subtype == LogitechClickSmart310) {
		xmult = 0x16;
		ymult = 0x12;
	} else {
		xmult = 0x28;
		ymult = 0x1e;
	}

	/* is there a sensor here ? */
	reg_r(gspca_dev, 0x8a04, 1);
	PDEBUG(D_STREAM, "Spca500 Sensor Address 0x%02x",
		gspca_dev->usb_buf[0]);
	PDEBUG(D_STREAM, "Spca500 curr_mode: %d Xmult: 0x%02x, Ymult: 0x%02x",
		gspca_dev->curr_mode, xmult, ymult);

	/* setup qtable */
	switch (sd->subtype) {
	case LogitechClickSmart310:
		 spca500_setmode(gspca_dev, xmult, ymult);

		/* enable drop packet */
		reg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		reg_w(gspca_dev, 0x00, 0x8880, 3);
		err = spca50x_setup_qtable(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtable_creative_pccam);
		if (err < 0)
			PDEBUG(D_ERR, "spca50x_setup_qtable failed");
		/* Init SDRAM - needed for SDRAM access */
		reg_w(gspca_dev, 0x00, 0x870a, 0x04);

		/* switch to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);
		msleep(500);
		if (reg_r_wait(gspca_dev, 0, 0x8000, 0x44) != 0)
			PDEBUG(D_ERR, "reg_r_wait() failed");

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);

		spca500_synch310(gspca_dev);

		write_vector(gspca_dev, spca500_visual_defaults);
		spca500_setmode(gspca_dev, xmult, ymult);
		/* enable drop packet */
		err = reg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		if (err < 0)
			PDEBUG(D_ERR, "failed to enable drop packet");
		reg_w(gspca_dev, 0x00, 0x8880, 3);
		err = spca50x_setup_qtable(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtable_creative_pccam);
		if (err < 0)
			PDEBUG(D_ERR, "spca50x_setup_qtable failed");

		/* Init SDRAM - needed for SDRAM access */
		reg_w(gspca_dev, 0x00, 0x870a, 0x04);

		/* switch to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		if (reg_r_wait(gspca_dev, 0, 0x8000, 0x44) != 0)
			PDEBUG(D_ERR, "reg_r_wait() failed");

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);
		break;
	case CreativePCCam300:		/* Creative PC-CAM 300 640x480 CCD */
	case IntelPocketPCCamera:	/* FIXME: Temporary fix for
					 *	Intel Pocket PC Camera
					 *	- NWG (Sat 29th March 2003) */

		/* do a full reset */
		err = spca500_full_reset(gspca_dev);
		if (err < 0)
			PDEBUG(D_ERR, "spca500_full_reset failed");

		/* enable drop packet */
		err = reg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		if (err < 0)
			PDEBUG(D_ERR, "failed to enable drop packet");
		reg_w(gspca_dev, 0x00, 0x8880, 3);
		err = spca50x_setup_qtable(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtable_creative_pccam);
		if (err < 0)
			PDEBUG(D_ERR, "spca50x_setup_qtable failed");

		spca500_setmode(gspca_dev, xmult, ymult);
		reg_w(gspca_dev, 0x20, 0x0001, 0x0004);

		/* switch to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		if (reg_r_wait(gspca_dev, 0, 0x8000, 0x44) != 0)
			PDEBUG(D_ERR, "reg_r_wait() failed");

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);

/*		write_vector(gspca_dev, spca500_visual_defaults); */
		break;
	case KodakEZ200:		/* Kodak EZ200 */

		/* do a full reset */
		err = spca500_full_reset(gspca_dev);
		if (err < 0)
			PDEBUG(D_ERR, "spca500_full_reset failed");
		/* enable drop packet */
		reg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		reg_w(gspca_dev, 0x00, 0x8880, 0);
		err = spca50x_setup_qtable(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtable_kodak_ez200);
		if (err < 0)
			PDEBUG(D_ERR, "spca50x_setup_qtable failed");
		spca500_setmode(gspca_dev, xmult, ymult);

		reg_w(gspca_dev, 0x20, 0x0001, 0x0004);

		/* switch to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		if (reg_r_wait(gspca_dev, 0, 0x8000, 0x44) != 0)
			PDEBUG(D_ERR, "reg_r_wait() failed");

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);

/*		write_vector(gspca_dev, spca500_visual_defaults); */
		break;

	case BenqDC1016:
	case DLinkDSC350:		/* FamilyCam 300 */
	case AiptekPocketDV:		/* Aiptek PocketDV */
	case Gsmartmini:		/*Mustek Gsmart Mini */
	case MustekGsmart300:		/* Mustek Gsmart 300 */
	case PalmPixDC85:
	case Optimedia:
	case ToptroIndus:
	case AgfaCl20:
		spca500_reinit(gspca_dev);
		reg_w(gspca_dev, 0x00, 0x0d01, 0x01);
		/* enable drop packet */
		reg_w(gspca_dev, 0x00, 0x850a, 0x0001);

		err = spca50x_setup_qtable(gspca_dev,
				   0x00, 0x8800, 0x8840, qtable_pocketdv);
		if (err < 0)
			PDEBUG(D_ERR, "spca50x_setup_qtable failed");
		reg_w(gspca_dev, 0x00, 0x8880, 2);

		/* familycam Quicksmart pocketDV stuff */
		reg_w(gspca_dev, 0x00, 0x800a, 0x00);
		/* Set agc transfer: synced inbetween frames */
		reg_w(gspca_dev, 0x00, 0x820f, 0x01);
		/* Init SDRAM - needed for SDRAM access */
		reg_w(gspca_dev, 0x00, 0x870a, 0x04);

		spca500_setmode(gspca_dev, xmult, ymult);
		/* switch to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		reg_r_wait(gspca_dev, 0, 0x8000, 0x44);

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);
		break;
	case LogitechTraveler:
	case LogitechClickSmart510:
		reg_w(gspca_dev, 0x02, 0x00, 0x00);
		/* enable drop packet */
		reg_w(gspca_dev, 0x00, 0x850a, 0x0001);

		err = spca50x_setup_qtable(gspca_dev,
					0x00, 0x8800,
					0x8840, qtable_creative_pccam);
		if (err < 0)
			PDEBUG(D_ERR, "spca50x_setup_qtable failed");
		reg_w(gspca_dev, 0x00, 0x8880, 3);
		reg_w(gspca_dev, 0x00, 0x800a, 0x00);
		/* Init SDRAM - needed for SDRAM access */
		reg_w(gspca_dev, 0x00, 0x870a, 0x04);

		spca500_setmode(gspca_dev, xmult, ymult);

		/* switch to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);
		reg_r_wait(gspca_dev, 0, 0x8000, 0x44);

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);
		write_vector(gspca_dev, Clicksmart510_defaults);
		break;
	}
	return 0;
}