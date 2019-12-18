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
struct sd {int model; scalar_t__ sof_read; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  err (char*) ; 
 int start_cif_cam (struct gspca_dev*) ; 
 int start_genius_cam (struct gspca_dev*) ; 
 int start_ms350_cam (struct gspca_dev*) ; 
 int start_spy_cam (struct gspca_dev*) ; 
 int start_vivitar_cam (struct gspca_dev*) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int err_code;

	sd->sof_read = 0;

	switch (sd->model) {
	case 0x7005:
		err_code = start_genius_cam(gspca_dev);
		break;
	case 0x8001:
		err_code = start_spy_cam(gspca_dev);
		break;
	case 0x8003:
		err_code = start_cif_cam(gspca_dev);
		break;
	case 0x8008:
		err_code = start_ms350_cam(gspca_dev);
		break;
	case 0x800a:
		err_code = start_vivitar_cam(gspca_dev);
		break;
	default:
		err("Starting unknown camera, please report this");
		return -ENXIO;
	}

	return err_code;
}