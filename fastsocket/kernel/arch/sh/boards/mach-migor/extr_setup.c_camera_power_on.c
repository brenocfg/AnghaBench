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
 int /*<<< orphan*/  GPIO_PTT0 ; 
 int /*<<< orphan*/  GPIO_PTT2 ; 
 int /*<<< orphan*/  GPIO_PTT3 ; 
 int /*<<< orphan*/  camera_clk ; 
 int /*<<< orphan*/  camera_lock ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void camera_power_on(int is_tw)
{
	mutex_lock(&camera_lock);

	/* Use 10 MHz VIO_CKO instead of 24 MHz to work
	 * around signal quality issues on Panel Board V2.1.
	 */
	camera_clk = clk_get(NULL, "video_clk");
	clk_set_rate(camera_clk, 10000000);
	clk_enable(camera_clk);	/* start VIO_CKO */

	/* use VIO_RST to take camera out of reset */
	mdelay(10);
	if (is_tw) {
		gpio_set_value(GPIO_PTT2, 0);
		gpio_set_value(GPIO_PTT0, 0);
	} else {
		gpio_set_value(GPIO_PTT0, 1);
	}
	gpio_set_value(GPIO_PTT3, 0);
	mdelay(10);
	gpio_set_value(GPIO_PTT3, 1);
	mdelay(10); /* wait to let chip come out of reset */
}