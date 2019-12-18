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
struct gspca_dev {int* usb_buf; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int const,int) ; 

__attribute__((used)) static void sensor_mapwrite(struct gspca_dev *gspca_dev,
			    const __u16 (*sensormap)[2])
{
	while ((*sensormap)[0]) {
		gspca_dev->usb_buf[0] = (*sensormap)[1];
		gspca_dev->usb_buf[1] = (*sensormap)[1] >> 8;
		reg_w_buf(gspca_dev, (*sensormap)[0], 2);
		sensormap++;
	}
}