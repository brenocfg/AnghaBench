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
struct sd {int /*<<< orphan*/  contrast; } ;
struct gspca_dev {int ctrl_dis; } ;

/* Variables and functions */
 int CONTRAST_IDX ; 
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void setcontrast(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (gspca_dev->ctrl_dis & (1 << CONTRAST_IDX))
		return;
	i2c_write(gspca_dev, 0x99, &sd->contrast, 1);
}