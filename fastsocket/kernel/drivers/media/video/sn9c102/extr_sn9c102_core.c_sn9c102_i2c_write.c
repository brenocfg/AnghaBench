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
typedef  int /*<<< orphan*/  u8 ;
struct sn9c102_device {int /*<<< orphan*/  sensor; } ;

/* Variables and functions */
 int sn9c102_i2c_try_write (struct sn9c102_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sn9c102_i2c_write(struct sn9c102_device* cam, u8 address, u8 value)
{
	return sn9c102_i2c_try_write(cam, &cam->sensor, address, value);
}