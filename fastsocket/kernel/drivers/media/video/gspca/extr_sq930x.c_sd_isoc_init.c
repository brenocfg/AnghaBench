#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {scalar_t__ do_ctrl; } ;
struct TYPE_2__ {int bulk_nurbs; int bulk_size; } ;
struct gspca_dev {int width; int height; TYPE_1__ cam; } ;

/* Variables and functions */

__attribute__((used)) static int sd_isoc_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	gspca_dev->cam.bulk_nurbs = 1;	/* there must be one URB only */
	sd->do_ctrl = 0;
	gspca_dev->cam.bulk_size = gspca_dev->width * gspca_dev->height + 8;
	return 0;
}