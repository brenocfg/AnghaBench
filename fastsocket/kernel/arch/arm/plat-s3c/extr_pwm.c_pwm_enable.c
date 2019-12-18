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
struct pwm_device {int running; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_TCON ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long pwm_tcon_start (struct pwm_device*) ; 

int pwm_enable(struct pwm_device *pwm)
{
	unsigned long flags;
	unsigned long tcon;

	local_irq_save(flags);

	tcon = __raw_readl(S3C2410_TCON);
	tcon |= pwm_tcon_start(pwm);
	__raw_writel(tcon, S3C2410_TCON);

	local_irq_restore(flags);

	pwm->running = 1;
	return 0;
}