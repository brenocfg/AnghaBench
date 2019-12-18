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
struct sd {int contrast; } ;
struct gspca_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void setcontrast(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	reg_write(gspca_dev->dev, 0x00, 0x00,
				  (sd->contrast >> 8) & 0xff);
	reg_write(gspca_dev->dev, 0x00, 0x01,
				  sd->contrast & 0xff);
}