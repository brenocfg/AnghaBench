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
struct azx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCTL ; 
 int ICH6_GCTL_RESET ; 
 int azx_readb (struct azx*,int /*<<< orphan*/ ) ; 
 int azx_readl (struct azx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  azx_writel (struct azx*,int /*<<< orphan*/ ,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void azx_enter_link_reset(struct azx *chip)
{
	unsigned long timeout;

	/* reset controller */
	azx_writel(chip, GCTL, azx_readl(chip, GCTL) & ~ICH6_GCTL_RESET);

	timeout = jiffies + msecs_to_jiffies(100);
	while ((azx_readb(chip, GCTL) & ICH6_GCTL_RESET) &&
			time_before(jiffies, timeout))
		usleep_range(500, 1000);
}