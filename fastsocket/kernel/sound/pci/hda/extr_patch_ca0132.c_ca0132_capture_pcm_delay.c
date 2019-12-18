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
struct snd_pcm_runtime {unsigned int rate; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__ dsp_state; scalar_t__* effects_switch; } ;

/* Variables and functions */
 size_t CRYSTAL_VOICE ; 
 unsigned int DSP_CAPTURE_INIT_LATENCY ; 
 scalar_t__ DSP_CRYSTAL_VOICE_LATENCY ; 
 scalar_t__ DSP_DOWNLOADED ; 
 size_t EFFECT_START_NID ; 

__attribute__((used)) static unsigned int ca0132_capture_pcm_delay(struct hda_pcm_stream *info,
			struct hda_codec *codec,
			struct snd_pcm_substream *substream)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int latency = DSP_CAPTURE_INIT_LATENCY;
	struct snd_pcm_runtime *runtime = substream->runtime;

	if (spec->dsp_state != DSP_DOWNLOADED)
		return 0;

	if (spec->effects_switch[CRYSTAL_VOICE - EFFECT_START_NID])
		latency += DSP_CRYSTAL_VOICE_LATENCY;

	return (latency * runtime->rate) / 1000;
}