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
struct pwm_device {scalar_t__ clk_div; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ clk_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pwm_is_tdiv(struct pwm_device *pwm)
{
	return clk_get_parent(pwm->clk) == pwm->clk_div;
}