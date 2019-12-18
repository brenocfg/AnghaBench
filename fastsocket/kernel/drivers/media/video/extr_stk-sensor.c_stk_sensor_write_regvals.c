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
struct stk_camera {int dummy; } ;
struct regval {int reg; int val; } ;

/* Variables and functions */
 int stk_sensor_outb (struct stk_camera*,int,int) ; 

__attribute__((used)) static int stk_sensor_write_regvals(struct stk_camera *dev,
		struct regval *rv)
{
	int ret;
	if (rv == NULL)
		return 0;
	while (rv->reg != 0xff || rv->val != 0xff) {
		ret = stk_sensor_outb(dev, rv->reg, rv->val);
		if (ret != 0)
			return ret;
		rv++;
	}
	return 0;
}