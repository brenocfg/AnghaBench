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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxc_gpio_release_multiple_pins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxc_uart1_pins ; 

__attribute__((used)) static int uart1_mxc_exit(struct platform_device *pdev)
{
	mxc_gpio_release_multiple_pins(mxc_uart1_pins,
			ARRAY_SIZE(mxc_uart1_pins));
	return 0;
}