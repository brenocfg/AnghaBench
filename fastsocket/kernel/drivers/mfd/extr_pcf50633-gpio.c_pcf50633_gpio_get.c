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
struct pcf50633 {int dummy; } ;

/* Variables and functions */
 int PCF50633_GPIO1 ; 
 int PCF50633_REG_GPIO1CFG ; 
 int pcf50633_reg_read (struct pcf50633*,int) ; 

u8 pcf50633_gpio_get(struct pcf50633 *pcf, int gpio)
{
	u8 reg, val;

	reg = gpio - PCF50633_GPIO1 + PCF50633_REG_GPIO1CFG;
	val = pcf50633_reg_read(pcf, reg) & 0x07;

	return val;
}