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
struct pwm_device {int /*<<< orphan*/  clk_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_get_parent (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_dbg (struct pwm_device*,char*,unsigned long) ; 

__attribute__((used)) static unsigned long pwm_calc_tin(struct pwm_device *pwm, unsigned long freq)
{
	unsigned long tin_parent_rate;
	unsigned int div;

	tin_parent_rate = clk_get_rate(clk_get_parent(pwm->clk_div));
	pwm_dbg(pwm, "tin parent at %lu\n", tin_parent_rate);

	for (div = 2; div <= 16; div *= 2) {
		if ((tin_parent_rate / (div << 16)) < freq)
			return tin_parent_rate / div;
	}

	return tin_parent_rate / 16;
}