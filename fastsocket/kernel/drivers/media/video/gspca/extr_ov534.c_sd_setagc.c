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
struct sd {scalar_t__ agc; } ;
struct gspca_dev {int ctrl_inac; scalar_t__ streaming; } ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 int AWB_IDX ; 
 int /*<<< orphan*/  setagc (struct gspca_dev*) ; 

__attribute__((used)) static int sd_setagc(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->agc = val;

	if (gspca_dev->streaming) {

		/* the auto white balance control works only
		 * when auto gain is set */
		if (val)
			gspca_dev->ctrl_inac &= ~(1 << AWB_IDX);
		else
			gspca_dev->ctrl_inac |= (1 << AWB_IDX);
		setagc(gspca_dev);
	}
	return 0;
}