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
struct ep93xx_pwm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_PWMx_INVERT ; 
 int ep93xx_pwm_readl (struct ep93xx_pwm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ep93xx_pwm_is_inverted(struct ep93xx_pwm *pwm)
{
	return ep93xx_pwm_readl(pwm, EP93XX_PWMx_INVERT) & 0x1;
}