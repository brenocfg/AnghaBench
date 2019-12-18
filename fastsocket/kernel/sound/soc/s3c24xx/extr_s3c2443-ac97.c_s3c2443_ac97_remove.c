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
struct snd_soc_dai {int dummy; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; int /*<<< orphan*/  ac97_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_S3C244x_AC97 ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 TYPE_1__ s3c24xx_ac97 ; 

__attribute__((used)) static void s3c2443_ac97_remove(struct platform_device *pdev,
				struct snd_soc_dai *dai)
{
	free_irq(IRQ_S3C244x_AC97, NULL);
	clk_disable(s3c24xx_ac97.ac97_clk);
	clk_put(s3c24xx_ac97.ac97_clk);
	iounmap(s3c24xx_ac97.regs);
}