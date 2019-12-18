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
struct pwm_device {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_div; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pwm_device*) ; 
 struct pwm_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int s3c_pwm_remove(struct platform_device *pdev)
{
	struct pwm_device *pwm = platform_get_drvdata(pdev);

	clk_put(pwm->clk_div);
	clk_put(pwm->clk);
	kfree(pwm);

	return 0;
}