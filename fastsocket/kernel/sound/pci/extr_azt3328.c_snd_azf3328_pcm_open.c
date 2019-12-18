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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct snd_azf3328 {TYPE_1__* codecs; } ;
typedef  enum snd_azf3328_codec_type { ____Placeholder_snd_azf3328_codec_type } snd_azf3328_codec_type ;
struct TYPE_2__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  snd_azf3328_dbgcallenter () ; 
 int /*<<< orphan*/  snd_azf3328_dbgcallleave () ; 
 int /*<<< orphan*/  snd_azf3328_hardware ; 
 int /*<<< orphan*/  snd_azf3328_hw_constraints_rates ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_azf3328* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int
snd_azf3328_pcm_open(struct snd_pcm_substream *substream,
		     enum snd_azf3328_codec_type codec_type
)
{
	struct snd_azf3328 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	snd_azf3328_dbgcallenter();
	chip->codecs[codec_type].substream = substream;

	/* same parameters for all our codecs - at least we think so... */
	runtime->hw = snd_azf3328_hardware;

	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &snd_azf3328_hw_constraints_rates);
	snd_azf3328_dbgcallleave();
	return 0;
}