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
struct mpu_config {scalar_t__ uart_mode; } ;

/* Variables and functions */
 struct mpu_config* dev_conf ; 
 scalar_t__ mpu_cmd (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpu401_prefix_cmd(int dev, unsigned char status)
{
	struct mpu_config *devc = &dev_conf[dev];

	if (devc->uart_mode)
		return 1;

	if (status < 0xf0)
	{
		if (mpu_cmd(dev, 0xD0, 0) < 0)
			return 0;
		return 1;
	}
	switch (status)
	{
		case 0xF0:
			if (mpu_cmd(dev, 0xDF, 0) < 0)
				return 0;
			return 1;

		default:
			return 0;
	}
}