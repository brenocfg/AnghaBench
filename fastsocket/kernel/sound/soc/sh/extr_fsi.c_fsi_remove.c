#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; int /*<<< orphan*/  irq; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fsi_free_dma_chan () ; 
 int /*<<< orphan*/  fsi_soc_dai ; 
 int /*<<< orphan*/  fsi_soc_platform ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* master ; 
 int /*<<< orphan*/  snd_soc_unregister_dais (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_unregister_platform (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsi_remove(struct platform_device *pdev)
{
	snd_soc_unregister_dais(fsi_soc_dai, ARRAY_SIZE(fsi_soc_dai));
	snd_soc_unregister_platform(&fsi_soc_platform);

	clk_put(master->clk);

	fsi_free_dma_chan();

	free_irq(master->irq, master);

	iounmap(master->base);
	kfree(master);
	master = NULL;
	return 0;
}