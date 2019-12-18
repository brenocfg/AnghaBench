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
struct sd {int model; int /*<<< orphan*/  lighting; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  CIT_IBM_NETCAM_PRO 133 
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int /*<<< orphan*/  cit_Packet_Format1 (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 
 int cit_model1_ntries ; 

__attribute__((used)) static void cit_set_lighting(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->model) {
	case CIT_MODEL0:
	case CIT_MODEL2:
	case CIT_MODEL3:
	case CIT_MODEL4:
	case CIT_IBM_NETCAM_PRO:
		break;
	case CIT_MODEL1: {
		int i;
		for (i = 0; i < cit_model1_ntries; i++)
			cit_Packet_Format1(gspca_dev, 0x0027, sd->lighting);
		break;
	}
	}
}