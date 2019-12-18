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
struct soc_camera_device {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MT9T031_BUS_PARAM ; 
 int /*<<< orphan*/  MT9T031_PIXEL_CLOCK_CONTROL ; 
 unsigned long SOCAM_PCLK_SAMPLE_FALLING ; 
 int /*<<< orphan*/  reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_set (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_soc_camera_control (struct soc_camera_device*) ; 

__attribute__((used)) static int mt9t031_set_bus_param(struct soc_camera_device *icd,
				 unsigned long flags)
{
	struct i2c_client *client = to_i2c_client(to_soc_camera_control(icd));

	/* The caller should have queried our parameters, check anyway */
	if (flags & ~MT9T031_BUS_PARAM)
		return -EINVAL;

	if (flags & SOCAM_PCLK_SAMPLE_FALLING)
		reg_clear(client, MT9T031_PIXEL_CLOCK_CONTROL, 0x8000);
	else
		reg_set(client, MT9T031_PIXEL_CLOCK_CONTROL, 0x8000);

	return 0;
}