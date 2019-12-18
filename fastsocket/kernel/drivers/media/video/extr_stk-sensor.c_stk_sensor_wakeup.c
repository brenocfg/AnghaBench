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
typedef  int u8 ;
struct stk_camera {int dummy; } ;

/* Variables and functions */
 int COM2_SSLEEP ; 
 int /*<<< orphan*/  REG_COM2 ; 
 scalar_t__ stk_sensor_inb (struct stk_camera*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stk_sensor_outb (struct stk_camera*,int /*<<< orphan*/ ,int) ; 

int stk_sensor_wakeup(struct stk_camera *dev)
{
	u8 tmp;
	return stk_sensor_inb(dev, REG_COM2, &tmp)
		|| stk_sensor_outb(dev, REG_COM2, tmp&~COM2_SSLEEP);
}