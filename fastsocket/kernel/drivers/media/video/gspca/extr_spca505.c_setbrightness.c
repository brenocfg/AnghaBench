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
typedef  int u8 ;
struct sd {int brightness; } ;
struct gspca_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void setbrightness(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 brightness = sd->brightness;

	reg_write(gspca_dev->dev, 0x05, 0x00, (255 - brightness) >> 6);
	reg_write(gspca_dev->dev, 0x05, 0x01, (255 - brightness) << 2);
}