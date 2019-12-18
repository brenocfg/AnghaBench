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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct sis7019 {int /*<<< orphan*/ * ac97; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_PCM_LR_ADC_RATE ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int sis_alloc_timing_voice (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int snd_ac97_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct sis7019* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int sis_capture_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *hw_params)
{
	struct sis7019 *sis = snd_pcm_substream_chip(substream);
	int rc;

	rc = snd_ac97_set_rate(sis->ac97[0], AC97_PCM_LR_ADC_RATE,
						params_rate(hw_params));
	if (rc)
		goto out;

	rc = snd_pcm_lib_malloc_pages(substream,
					params_buffer_bytes(hw_params));
	if (rc < 0)
		goto out;

	rc = sis_alloc_timing_voice(substream, hw_params);

out:
	return rc;
}