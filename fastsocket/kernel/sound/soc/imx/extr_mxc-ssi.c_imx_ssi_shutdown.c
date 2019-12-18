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
struct snd_soc_pcm_runtime {TYPE_1__* dai; } ;
struct snd_soc_dai {scalar_t__ id; int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_2__ {struct snd_soc_dai* cpu_dai; } ;

/* Variables and functions */
 scalar_t__ IMX_DAI_SSI0 ; 
 scalar_t__ IMX_DAI_SSI2 ; 
 size_t SSI1_PORT ; 
 scalar_t__ SSI1_SCR ; 
 size_t SSI2_PORT ; 
 scalar_t__ SSI2_SCR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int* ssi_active ; 
 int /*<<< orphan*/  ssi_clk0 ; 
 int /*<<< orphan*/  ssi_clk1 ; 

__attribute__((used)) static void imx_ssi_shutdown(struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;

	/* shutdown SSI if neither Tx or Rx is active */
	if (!cpu_dai->active) {

		if (cpu_dai->id == IMX_DAI_SSI0 ||
			cpu_dai->id == IMX_DAI_SSI2) {

			if (--ssi_active[SSI1_PORT] > 1)
				return;

			SSI1_SCR = 0;
			clk_disable(ssi_clk0);
		} else {
			if (--ssi_active[SSI2_PORT])
				return;
			SSI2_SCR = 0;
			clk_disable(ssi_clk1);
		}
	}
}