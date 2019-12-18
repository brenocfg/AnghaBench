#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssi_priv {int inuse; } ;
struct snd_soc_pcm_runtime {TYPE_2__* dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_4__ {TYPE_1__* cpu_dai; } ;
struct TYPE_3__ {size_t id; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct ssi_priv* ssi_cpu_data ; 

__attribute__((used)) static int ssi_startup(struct snd_pcm_substream *substream,
		       struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct ssi_priv *ssi = &ssi_cpu_data[rtd->dai->cpu_dai->id];
	if (ssi->inuse) {
		pr_debug("ssi: already in use!\n");
		return -EBUSY;
	} else
		ssi->inuse = 1;
	return 0;
}