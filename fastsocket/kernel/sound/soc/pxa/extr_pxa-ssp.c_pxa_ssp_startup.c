#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* ssp; int /*<<< orphan*/  irq; scalar_t__ port; } ;
struct ssp_priv {TYPE_3__ dev; } ;
struct snd_soc_pcm_runtime {TYPE_1__* dai; } ;
struct snd_soc_dai {int /*<<< orphan*/ * dma_data; scalar_t__ id; int /*<<< orphan*/  active; struct ssp_priv* private_data; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  clk; } ;
struct TYPE_4__ {struct snd_soc_dai* cpu_dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_IRQ ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssp_disable (TYPE_3__*) ; 

__attribute__((used)) static int pxa_ssp_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;
	struct ssp_priv *priv = cpu_dai->private_data;
	int ret = 0;

	if (!cpu_dai->active) {
		priv->dev.port = cpu_dai->id + 1;
		priv->dev.irq = NO_IRQ;
		clk_enable(priv->dev.ssp->clk);
		ssp_disable(&priv->dev);
	}

	if (cpu_dai->dma_data) {
		kfree(cpu_dai->dma_data);
		cpu_dai->dma_data = NULL;
	}
	return ret;
}