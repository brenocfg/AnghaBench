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
 int /*<<< orphan*/  cit_init_ibm_netcam_pro (struct gspca_dev*) ; 
 int /*<<< orphan*/  cit_init_model0 (struct gspca_dev*) ; 
 int /*<<< orphan*/  sd_stop0 (struct gspca_dev*) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->model) {
	case CIT_MODEL0:
		cit_init_model0(gspca_dev);
		sd_stop0(gspca_dev);
		break;
	case CIT_MODEL1:
	case CIT_MODEL2:
	case CIT_MODEL3:
	case CIT_MODEL4:
		break; /* All is done in sd_start */
	case CIT_IBM_NETCAM_PRO:
		cit_init_ibm_netcam_pro(gspca_dev);
		sd_stop0(gspca_dev);
		break;
	}
	return 0;
}