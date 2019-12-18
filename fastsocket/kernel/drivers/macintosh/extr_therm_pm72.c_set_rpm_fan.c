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
struct TYPE_2__ {scalar_t__ type; int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int FCU_FAN_ABSENT_ID ; 
 scalar_t__ FCU_FAN_RPM ; 
 int fan_write_reg (int,unsigned char*,int) ; 
 TYPE_1__* fcu_fans ; 
 int fcu_rpm_shift ; 

__attribute__((used)) static int set_rpm_fan(int fan_index, int rpm)
{
	unsigned char buf[2];
	int rc, id, min, max;

	if (fcu_fans[fan_index].type != FCU_FAN_RPM)
		return -EINVAL;
	id = fcu_fans[fan_index].id; 
	if (id == FCU_FAN_ABSENT_ID)
		return -EINVAL;

	min = 2400 >> fcu_rpm_shift;
	max = 56000 >> fcu_rpm_shift;

	if (rpm < min)
		rpm = min;
	else if (rpm > max)
		rpm = max;
	buf[0] = rpm >> (8 - fcu_rpm_shift);
	buf[1] = rpm << fcu_rpm_shift;
	rc = fan_write_reg(0x10 + (id * 2), buf, 2);
	if (rc < 0)
		return -EIO;
	return 0;
}