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
struct snd_soc_pcm_runtime {TYPE_2__* dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct fsi_priv {int dummy; } ;
struct TYPE_6__ {struct fsi_priv fsib; struct fsi_priv fsia; } ;
struct TYPE_5__ {TYPE_1__* cpu_dai; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 TYPE_3__* master ; 

__attribute__((used)) static struct fsi_priv *fsi_get(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd;
	struct fsi_priv *fsi = NULL;

	if (!substream || !master)
		return NULL;

	rtd = substream->private_data;
	switch (rtd->dai->cpu_dai->id) {
	case 0:
		fsi = &master->fsia;
		break;
	case 1:
		fsi = &master->fsib;
		break;
	}

	return fsi;
}