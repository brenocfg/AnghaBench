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
struct sn9c102_sensor {int dummy; } ;
struct sn9c102_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int sn9c102_read_reg (struct sn9c102_device*,int) ; 

__attribute__((used)) static int
sn9c102_i2c_detect_write_error(struct sn9c102_device* cam,
			       const struct sn9c102_sensor* sensor)
{
	int r;
	r = sn9c102_read_reg(cam, 0x08);
	return (r < 0 || (r >= 0 && (r & 0x08))) ? -EIO : 0;
}