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
struct bbc_fan_control {scalar_t__ cpu_fan_speed; scalar_t__ system_fan_speed; scalar_t__ psupply_fan_on; int /*<<< orphan*/  client; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FAN_REG ; 
 scalar_t__ FAN_SPEED_MAX ; 
 scalar_t__ FAN_SPEED_MIN ; 
 scalar_t__ PSUPPLY_FAN_OFF ; 
 scalar_t__ PSUPPLY_FAN_ON ; 
 int /*<<< orphan*/  PSUPPLY_FAN_REG ; 
 int /*<<< orphan*/  SYS_FAN_REG ; 
 int /*<<< orphan*/  bbc_i2c_writeb (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void set_fan_speeds(struct bbc_fan_control *fp)
{
	/* Put temperatures into range so we don't mis-program
	 * the hardware.
	 */
	if (fp->cpu_fan_speed < FAN_SPEED_MIN)
		fp->cpu_fan_speed = FAN_SPEED_MIN;
	if (fp->cpu_fan_speed > FAN_SPEED_MAX)
		fp->cpu_fan_speed = FAN_SPEED_MAX;
	if (fp->system_fan_speed < FAN_SPEED_MIN)
		fp->system_fan_speed = FAN_SPEED_MIN;
	if (fp->system_fan_speed > FAN_SPEED_MAX)
		fp->system_fan_speed = FAN_SPEED_MAX;
#ifdef ENVCTRL_TRACE
	printk("fan%d: Changed fan speed to cpu(%02x) sys(%02x)\n",
	       fp->index,
	       fp->cpu_fan_speed, fp->system_fan_speed);
#endif

	bbc_i2c_writeb(fp->client, fp->cpu_fan_speed, CPU_FAN_REG);
	bbc_i2c_writeb(fp->client, fp->system_fan_speed, SYS_FAN_REG);
	bbc_i2c_writeb(fp->client,
		       (fp->psupply_fan_on ?
			PSUPPLY_FAN_ON : PSUPPLY_FAN_OFF),
		       PSUPPLY_FAN_REG);
}