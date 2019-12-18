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
typedef  int uint8_t ;
struct mx3fb_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDC_PWM_CTRL ; 
 int /*<<< orphan*/  mx3fb_write_reg (struct mx3fb_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdc_set_brightness(struct mx3fb_data *mx3fb, uint8_t value)
{
	/* This might be board-specific */
	mx3fb_write_reg(mx3fb, 0x03000000UL | value << 16, SDC_PWM_CTRL);
	return;
}