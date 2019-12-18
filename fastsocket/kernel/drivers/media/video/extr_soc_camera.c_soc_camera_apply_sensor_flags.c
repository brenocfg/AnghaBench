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
struct soc_camera_link {int flags; } ;

/* Variables and functions */
 unsigned long SOCAM_HSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_HSYNC_ACTIVE_LOW ; 
 unsigned long SOCAM_PCLK_SAMPLE_FALLING ; 
 unsigned long SOCAM_PCLK_SAMPLE_RISING ; 
 int SOCAM_SENSOR_INVERT_HSYNC ; 
 int SOCAM_SENSOR_INVERT_PCLK ; 
 int SOCAM_SENSOR_INVERT_VSYNC ; 
 unsigned long SOCAM_VSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_VSYNC_ACTIVE_LOW ; 

unsigned long soc_camera_apply_sensor_flags(struct soc_camera_link *icl,
					    unsigned long flags)
{
	unsigned long f;

	/* If only one of the two polarities is supported, switch to the opposite */
	if (icl->flags & SOCAM_SENSOR_INVERT_HSYNC) {
		f = flags & (SOCAM_HSYNC_ACTIVE_HIGH | SOCAM_HSYNC_ACTIVE_LOW);
		if (f == SOCAM_HSYNC_ACTIVE_HIGH || f == SOCAM_HSYNC_ACTIVE_LOW)
			flags ^= SOCAM_HSYNC_ACTIVE_HIGH | SOCAM_HSYNC_ACTIVE_LOW;
	}

	if (icl->flags & SOCAM_SENSOR_INVERT_VSYNC) {
		f = flags & (SOCAM_VSYNC_ACTIVE_HIGH | SOCAM_VSYNC_ACTIVE_LOW);
		if (f == SOCAM_VSYNC_ACTIVE_HIGH || f == SOCAM_VSYNC_ACTIVE_LOW)
			flags ^= SOCAM_VSYNC_ACTIVE_HIGH | SOCAM_VSYNC_ACTIVE_LOW;
	}

	if (icl->flags & SOCAM_SENSOR_INVERT_PCLK) {
		f = flags & (SOCAM_PCLK_SAMPLE_RISING | SOCAM_PCLK_SAMPLE_FALLING);
		if (f == SOCAM_PCLK_SAMPLE_RISING || f == SOCAM_PCLK_SAMPLE_FALLING)
			flags ^= SOCAM_PCLK_SAMPLE_RISING | SOCAM_PCLK_SAMPLE_FALLING;
	}

	return flags;
}