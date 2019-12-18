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
 int /*<<< orphan*/  ep93xx_pwm_writel (struct ep93xx_pwm*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ep93xx_pwm_invert(struct ep93xx_pwm *pwm)
{
	ep93xx_pwm_writel(pwm, 0x1, EP93XX_PWMx_INVERT);
}