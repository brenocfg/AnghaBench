#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int id; } ;
struct snd_pcm_substream {int stream; int number; TYPE_3__* pcm; TYPE_2__ dma_device; struct snd_pcm_substream* next; } ;
struct snd_pcm {TYPE_1__* streams; } ;
struct snd_mixart {int chip_idx; TYPE_4__* mgr; } ;
struct TYPE_8__ {int /*<<< orphan*/  pci; } ;
struct TYPE_7__ {int device; } ;
struct TYPE_5__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages_for_all (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void preallocate_buffers(struct snd_mixart *chip, struct snd_pcm *pcm)
{
#if 0
	struct snd_pcm_substream *subs;
	int stream;

	for (stream = 0; stream < 2; stream++) {
		int idx = 0;
		for (subs = pcm->streams[stream].substream; subs; subs = subs->next, idx++)
			/* set up the unique device id with the chip index */
			subs->dma_device.id = subs->pcm->device << 16 |
				subs->stream << 8 | (subs->number + 1) |
				(chip->chip_idx + 1) << 24;
	}
#endif
	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->mgr->pci), 32*1024, 32*1024);
}