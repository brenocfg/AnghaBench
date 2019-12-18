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
struct g760a_data {int /*<<< orphan*/  set_cnt; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PWM_FROM_CNT (int /*<<< orphan*/ ) ; 
 struct g760a_data* g760a_update_client (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t get_pwm(struct device *dev, struct device_attribute *da,
		       char *buf)
{
	struct g760a_data *data = g760a_update_client(dev);

	return sprintf(buf, "%d\n", PWM_FROM_CNT(data->set_cnt));
}