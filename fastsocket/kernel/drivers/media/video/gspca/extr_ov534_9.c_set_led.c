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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void set_led(struct gspca_dev *gspca_dev, int status)
{
	u8 data;

	PDEBUG(D_CONF, "led status: %d", status);

	data = reg_r(gspca_dev, 0x21);
	data |= 0x80;
	reg_w(gspca_dev, 0x21, data);

	data = reg_r(gspca_dev, 0x23);
	if (status)
		data |= 0x80;
	else
		data &= ~0x80;

	reg_w(gspca_dev, 0x23, data);

	if (!status) {
		data = reg_r(gspca_dev, 0x21);
		data &= ~0x80;
		reg_w(gspca_dev, 0x21, data);
	}
}