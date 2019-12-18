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
struct snd_usX2Y_substream {struct snd_pcm_substream* pcm_substream; TYPE_1__* usX2Y; } ;
struct snd_pcm_substream {size_t stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_usX2Y_substream* private_data; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int chip_status; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_TIME ; 
 int USX2Y_STAT_CHIP_MMAP_PCM_URBS ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_usX2Y_2c ; 

__attribute__((used)) static int snd_usX2Y_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_usX2Y_substream	*subs = ((struct snd_usX2Y_substream **)
					 snd_pcm_substream_chip(substream))[substream->stream];
	struct snd_pcm_runtime	*runtime = substream->runtime;

	if (subs->usX2Y->chip_status & USX2Y_STAT_CHIP_MMAP_PCM_URBS)
		return -EBUSY;

	runtime->hw = snd_usX2Y_2c;
	runtime->private_data = subs;
	subs->pcm_substream = substream;
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_PERIOD_TIME, 1000, 200000);
	return 0;
}