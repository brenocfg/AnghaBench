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
typedef  int u8 ;
struct lm93_data {int** block9; long* pwm_override; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 size_t LM93_PWM_CTL2 ; 
 size_t LM93_PWM_CTL4 ; 
 long LM93_PWM_FROM_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM93_PWM_MAP_HI_FREQ ; 
 int /*<<< orphan*/  LM93_PWM_MAP_LO_FREQ ; 
 struct lm93_data* lm93_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_pwm(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	int nr = (to_sensor_dev_attr(attr))->index;
	struct lm93_data *data = lm93_update_device(dev);
	u8 ctl2, ctl4;
	long rc;

	ctl2 = data->block9[nr][LM93_PWM_CTL2];
	ctl4 = data->block9[nr][LM93_PWM_CTL4];
	if (ctl2 & 0x01) /* show user commanded value if enabled */
		rc = data->pwm_override[nr];
	else /* show present h/w value if manual pwm disabled */
		rc = LM93_PWM_FROM_REG(ctl2 >> 4, (ctl4 & 0x07) ?
			LM93_PWM_MAP_LO_FREQ : LM93_PWM_MAP_HI_FREQ);
	return sprintf(buf,"%ld\n",rc);
}