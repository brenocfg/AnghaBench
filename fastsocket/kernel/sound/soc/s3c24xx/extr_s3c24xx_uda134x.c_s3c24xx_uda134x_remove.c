#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  l3_mode; int /*<<< orphan*/  l3_clk; int /*<<< orphan*/  l3_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 TYPE_1__* s3c24xx_uda134x_l3_pins ; 
 int /*<<< orphan*/  s3c24xx_uda134x_snd_device ; 

__attribute__((used)) static int s3c24xx_uda134x_remove(struct platform_device *pdev)
{
	platform_device_unregister(s3c24xx_uda134x_snd_device);
	gpio_free(s3c24xx_uda134x_l3_pins->l3_data);
	gpio_free(s3c24xx_uda134x_l3_pins->l3_clk);
	gpio_free(s3c24xx_uda134x_l3_pins->l3_mode);
	return 0;
}