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
struct sd {int model; int hue; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  CIT_IBM_NETCAM_PRO 133 
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int /*<<< orphan*/  cit_model2_Packet1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  cit_model3_Packet1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  cit_write_reg (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int cit_set_hue(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->model) {
	case CIT_MODEL0:
	case CIT_MODEL1:
	case CIT_IBM_NETCAM_PRO:
		/* No hue control for these models */
		break;
	case CIT_MODEL2:
		cit_model2_Packet1(gspca_dev, 0x0024, sd->hue);
		/* cit_model2_Packet1(gspca_dev, 0x0020, sat); */
		break;
	case CIT_MODEL3: {
		/* Model 3: Brightness range 'i' in [0x05..0x37] */
		/* TESTME according to the ibmcam driver this does not work */
		if (0) {
			/* Scale 0 - 127 to 0x05 - 0x37 */
			int i = 0x05 + sd->hue * 1000 / 2540;
			cit_model3_Packet1(gspca_dev, 0x007e, i);
		}
		break;
	}
	case CIT_MODEL4:
		/* HDG: taken from ibmcam, setting the color gains does not
		 * really belong here.
		 *
		 * I am not sure r/g/b_gain variables exactly control gain
		 * of those channels. Most likely they subtly change some
		 * very internal image processing settings in the camera.
		 * In any case, here is what they do, and feel free to tweak:
		 *
		 * r_gain: seriously affects red gain
		 * g_gain: seriously affects green gain
		 * b_gain: seriously affects blue gain
		 * hue: changes average color from violet (0) to red (0xFF)
		 */
		cit_write_reg(gspca_dev, 0x00aa, 0x012d);
		cit_write_reg(gspca_dev, 0x001e, 0x012f);
		cit_write_reg(gspca_dev, 0xd141, 0x0124);
		cit_write_reg(gspca_dev,    160, 0x0127);  /* Green gain */
		cit_write_reg(gspca_dev,    160, 0x012e);  /* Red gain */
		cit_write_reg(gspca_dev,    160, 0x0130);  /* Blue gain */
		cit_write_reg(gspca_dev, 0x8a28, 0x0124);
		cit_write_reg(gspca_dev, sd->hue, 0x012d); /* Hue */
		cit_write_reg(gspca_dev, 0xf545, 0x0124);
		break;
	}
	return 0;
}