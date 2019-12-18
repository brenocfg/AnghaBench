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
 int /*<<< orphan*/  GCR ; 
 int /*<<< orphan*/  GCR_ACLINK_OFF ; 
 int /*<<< orphan*/  IRQ_AC97 ; 
 int /*<<< orphan*/ * ac97_clk ; 
 int /*<<< orphan*/ * ac97conf_clk ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pxa2xx_ac97_hw_remove(struct platform_device *dev)
{
	GCR |= GCR_ACLINK_OFF;
	free_irq(IRQ_AC97, NULL);
	if (ac97conf_clk) {
		clk_put(ac97conf_clk);
		ac97conf_clk = NULL;
	}
	clk_disable(ac97_clk);
	clk_put(ac97_clk);
	ac97_clk = NULL;
}