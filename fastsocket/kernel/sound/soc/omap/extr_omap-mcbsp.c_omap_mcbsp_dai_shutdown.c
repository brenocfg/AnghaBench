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
struct snd_soc_dai {int /*<<< orphan*/  active; int /*<<< orphan*/  private_data; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct omap_mcbsp_data {scalar_t__ configured; int /*<<< orphan*/  bus_id; } ;
struct TYPE_2__ {struct snd_soc_dai* cpu_dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_mcbsp_free (int /*<<< orphan*/ ) ; 
 struct omap_mcbsp_data* to_mcbsp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_mcbsp_dai_shutdown(struct snd_pcm_substream *substream,
				    struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;
	struct omap_mcbsp_data *mcbsp_data = to_mcbsp(cpu_dai->private_data);

	if (!cpu_dai->active) {
		omap_mcbsp_free(mcbsp_data->bus_id);
		mcbsp_data->configured = 0;
	}
}