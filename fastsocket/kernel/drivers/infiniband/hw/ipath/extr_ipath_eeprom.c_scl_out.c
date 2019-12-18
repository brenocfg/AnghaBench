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
typedef  scalar_t__ u8 ;
struct ipath_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_gpio_set (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_line_high ; 
 int /*<<< orphan*/  i2c_line_low ; 
 int /*<<< orphan*/  i2c_line_scl ; 
 int /*<<< orphan*/  i2c_wait_for_writes (struct ipath_devdata*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void scl_out(struct ipath_devdata *dd, u8 bit)
{
	udelay(1);
	i2c_gpio_set(dd, i2c_line_scl, bit ? i2c_line_high : i2c_line_low);

	i2c_wait_for_writes(dd);
}