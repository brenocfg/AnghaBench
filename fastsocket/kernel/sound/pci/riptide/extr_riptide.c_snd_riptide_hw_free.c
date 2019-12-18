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
struct snd_riptide {struct cmdif* cif; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * area; } ;
struct pcmhw {int source; int* intdec; TYPE_1__ sgdlist; int /*<<< orphan*/ * lbuspath; } ;
struct cmdif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  freelbuspath (struct cmdif*,int,int /*<<< orphan*/ *) ; 
 struct pcmhw* get_pcmhwdev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_riptide* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_riptide_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_riptide *chip = snd_pcm_substream_chip(substream);
	struct pcmhw *data = get_pcmhwdev(substream);
	struct cmdif *cif = chip->cif;

	if (cif && data) {
		if (data->lbuspath)
			freelbuspath(cif, data->source, data->lbuspath);
		data->lbuspath = NULL;
		data->source = 0xff;
		data->intdec[0] = 0xff;
		data->intdec[1] = 0xff;

		if (data->sgdlist.area) {
			snd_dma_free_pages(&data->sgdlist);
			data->sgdlist.area = NULL;
		}
	}
	return snd_pcm_lib_free_pages(substream);
}