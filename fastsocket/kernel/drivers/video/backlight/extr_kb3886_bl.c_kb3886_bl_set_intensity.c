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

/* Variables and functions */
 int KB3886_ADC_DAC_PWM ; 
 int /*<<< orphan*/  KB3886_IO ; 
 int /*<<< orphan*/  KB3886_PARENT ; 
 int KB3886_PWM0_WRITE ; 
 int /*<<< orphan*/  bl_mutex ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kb3886_bl_set_intensity(int intensity)
{
	mutex_lock(&bl_mutex);
	intensity = intensity&0xff;
	outb(KB3886_ADC_DAC_PWM, KB3886_PARENT);
	msleep(10);
	outb(KB3886_PWM0_WRITE, KB3886_IO);
	msleep(10);
	outb(intensity, KB3886_IO);
	mutex_unlock(&bl_mutex);
}