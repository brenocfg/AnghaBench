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
 int FCU_FAN_ABSENT_ID ; 
 scalar_t__ FCU_FAN_PWM ; 
 int fan_write_reg (int,unsigned char*,int) ; 
 TYPE_1__* fcu_fans ; 

__attribute__((used)) static int set_pwm_fan(int fan_index, int pwm)
{
	unsigned char buf[2];
	int rc, id;

	if (fcu_fans[fan_index].type != FCU_FAN_PWM)
		return -EINVAL;
	id = fcu_fans[fan_index].id; 
	if (id == FCU_FAN_ABSENT_ID)
		return -EINVAL;

	if (pwm < 10)
		pwm = 10;
	else if (pwm > 100)
		pwm = 100;
	pwm = (pwm * 2559) / 1000;
	buf[0] = pwm;
	rc = fan_write_reg(0x30 + (id * 2), buf, 1);
	if (rc < 0)
		return rc;
	return 0;
}