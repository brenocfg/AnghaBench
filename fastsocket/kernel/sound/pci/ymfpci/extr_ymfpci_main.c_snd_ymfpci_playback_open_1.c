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
struct snd_ymfpci_pcm {struct snd_pcm_substream* substream; int /*<<< orphan*/  type; struct snd_ymfpci* chip; } ;
struct snd_ymfpci {int dummy; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  private_free; struct snd_ymfpci_pcm* private_data; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PLAYBACK_VOICE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_TIME ; 
 int /*<<< orphan*/  UINT_MAX ; 
 struct snd_ymfpci_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct snd_ymfpci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ymfpci_pcm_free_substream ; 
 int /*<<< orphan*/  snd_ymfpci_playback ; 

__attribute__((used)) static int snd_ymfpci_playback_open_1(struct snd_pcm_substream *substream)
{
	struct snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ymfpci_pcm *ypcm;

	ypcm = kzalloc(sizeof(*ypcm), GFP_KERNEL);
	if (ypcm == NULL)
		return -ENOMEM;
	ypcm->chip = chip;
	ypcm->type = PLAYBACK_VOICE;
	ypcm->substream = substream;
	runtime->hw = snd_ymfpci_playback;
	runtime->private_data = ypcm;
	runtime->private_free = snd_ymfpci_pcm_free_substream;
	/* FIXME? True value is 256/48 = 5.33333 ms */
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_PERIOD_TIME, 5333, UINT_MAX);
	return 0;
}