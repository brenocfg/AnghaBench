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
struct sd {int subtype; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  Arowana300KCMOSCamera 130 
 int /*<<< orphan*/  D_STREAM ; 
 int EINVAL ; 
#define  MystFromOriUnknownCamera 129 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
#define  SmileIntlCamera 128 
 int /*<<< orphan*/  spca501_init_data ; 
 int /*<<< orphan*/  spca501c_arowana_init_data ; 
 int /*<<< orphan*/  spca501c_mysterious_open_data ; 
 int /*<<< orphan*/  write_vector (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->subtype) {
	case Arowana300KCMOSCamera:
	case SmileIntlCamera:
		/* Arowana 300k CMOS Camera data */
		if (write_vector(gspca_dev, spca501c_arowana_init_data))
			goto error;
		break;
	case MystFromOriUnknownCamera:
		/* Unknown Ori CMOS Camera data */
		if (write_vector(gspca_dev, spca501c_mysterious_open_data))
			goto error;
		break;
	default:
		/* generic spca501 init data */
		if (write_vector(gspca_dev, spca501_init_data))
			goto error;
		break;
	}
	PDEBUG(D_STREAM, "Initializing SPCA501 finished");
	return 0;
error:
	return -EINVAL;
}