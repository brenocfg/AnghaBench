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
struct sd {int model; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  CIT_IBM_NETCAM_PRO 133 
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int cit_get_packet_size (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_restart_stream (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_set_brightness (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_set_contrast (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_set_hflip (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_set_hue (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_set_lighting (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_set_sharpness (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_start_ibm_netcam_pro (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_start_model0 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_start_model1 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_start_model2 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_start_model3 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_start_model4 (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_write_reg (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int packet_size;

	packet_size = cit_get_packet_size(gspca_dev);
	if (packet_size < 0)
		return packet_size;

	switch (sd->model) {
	case CIT_MODEL0:
		cit_start_model0(gspca_dev);
		break;
	case CIT_MODEL1:
		cit_start_model1(gspca_dev);
		break;
	case CIT_MODEL2:
		cit_start_model2(gspca_dev);
		break;
	case CIT_MODEL3:
		cit_start_model3(gspca_dev);
		break;
	case CIT_MODEL4:
		cit_start_model4(gspca_dev);
		break;
	case CIT_IBM_NETCAM_PRO:
		cit_start_ibm_netcam_pro(gspca_dev);
		break;
	}

	cit_set_brightness(gspca_dev);
	cit_set_contrast(gspca_dev);
	cit_set_hue(gspca_dev);
	cit_set_sharpness(gspca_dev);
	cit_set_lighting(gspca_dev);
	cit_set_hflip(gspca_dev);

	/* Program max isoc packet size */
	cit_write_reg(gspca_dev, packet_size >> 8, 0x0106);
	cit_write_reg(gspca_dev, packet_size & 0xff, 0x0107);

	cit_restart_stream(gspca_dev);

	return 0;
}