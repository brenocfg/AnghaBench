#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_ymfpci_pcm {size_t capture_bank_number; } ;
struct snd_ymfpci {int /*<<< orphan*/ ** capture_substream; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_ymfpci_pcm* private_data; } ;

/* Variables and functions */
 struct snd_ymfpci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ymfpci_hw_stop (struct snd_ymfpci*) ; 

__attribute__((used)) static int snd_ymfpci_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ymfpci_pcm *ypcm = runtime->private_data;

	if (ypcm != NULL) {
		chip->capture_substream[ypcm->capture_bank_number] = NULL;
		snd_ymfpci_hw_stop(chip);
	}
	return 0;
}