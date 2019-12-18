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
struct w9968cf_device {int dummy; } ;

/* Variables and functions */
 int w9968cf_write_reg (struct w9968cf_device*,int,int) ; 

__attribute__((used)) static int w9968cf_smbus_refresh_bus(struct w9968cf_device* cam)
{
	int err = 0, j;

	for (j = 1; j <= 10; j++) {
		err = w9968cf_write_reg(cam, 0x0020, 0x01);
		err += w9968cf_write_reg(cam, 0x0000, 0x01);
		if (err)
			break;
	}

	return err;
}