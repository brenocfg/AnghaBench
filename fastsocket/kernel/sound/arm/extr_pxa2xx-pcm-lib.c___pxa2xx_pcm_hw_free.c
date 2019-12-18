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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct pxa2xx_runtime_data {TYPE_2__* params; } ;
struct TYPE_4__ {scalar_t__* drcmr; } ;
struct TYPE_3__ {struct pxa2xx_runtime_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

int __pxa2xx_pcm_hw_free(struct snd_pcm_substream *substream)
{
	struct pxa2xx_runtime_data *rtd = substream->runtime->private_data;

	if (rtd && rtd->params && rtd->params->drcmr)
		*rtd->params->drcmr = 0;

	snd_pcm_set_runtime_buffer(substream, NULL);
	return 0;
}