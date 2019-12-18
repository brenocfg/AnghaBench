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
struct pwm_device {scalar_t__ clk_enabled; int /*<<< orphan*/  clk; scalar_t__ mmio_base; } ;

/* Variables and functions */
 scalar_t__ MX3_PWMCR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void pwm_disable(struct pwm_device *pwm)
{
	writel(0, pwm->mmio_base + MX3_PWMCR);

	if (pwm->clk_enabled) {
		clk_disable(pwm->clk);
		pwm->clk_enabled = 0;
	}
}