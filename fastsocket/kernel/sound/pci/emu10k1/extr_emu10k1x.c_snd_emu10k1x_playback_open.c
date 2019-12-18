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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; int /*<<< orphan*/  private_free; struct emu10k1x_pcm* private_data; } ;
struct emu10k1x_pcm {struct snd_pcm_substream* substream; struct emu10k1x* emu; } ;
struct emu10k1x {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 struct emu10k1x_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1x_pcm_free_substream ; 
 int /*<<< orphan*/  snd_emu10k1x_playback_hw ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct emu10k1x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_emu10k1x_playback_open(struct snd_pcm_substream *substream)
{
	struct emu10k1x *chip = snd_pcm_substream_chip(substream);
	struct emu10k1x_pcm *epcm;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	if ((err = snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS)) < 0) {
		return err;
	}
	if ((err = snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64)) < 0)
                return err;

	epcm = kzalloc(sizeof(*epcm), GFP_KERNEL);
	if (epcm == NULL)
		return -ENOMEM;
	epcm->emu = chip;
	epcm->substream = substream;
  
	runtime->private_data = epcm;
	runtime->private_free = snd_emu10k1x_pcm_free_substream;
  
	runtime->hw = snd_emu10k1x_playback_hw;

	return 0;
}