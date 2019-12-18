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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct parsed_hdmi_eld {int sad_count; struct cea_sad* sad; } ;
struct hda_pcm_stream {int rates; void* channels_max; void* maxbps; int /*<<< orphan*/  formats; } ;
struct cea_sad {int rates; unsigned int channels; scalar_t__ format; int sample_bits; } ;

/* Variables and functions */
 int AC_SUPPCM_BITS_20 ; 
 int AC_SUPPCM_BITS_24 ; 
 scalar_t__ AUDIO_CODING_TYPE_LPCM ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S16_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S32_LE ; 
 int SNDRV_PCM_RATE_32000 ; 
 int SNDRV_PCM_RATE_44100 ; 
 int SNDRV_PCM_RATE_48000 ; 
 void* min (void*,unsigned int) ; 

void snd_hdmi_eld_update_pcm_info(struct parsed_hdmi_eld *e,
			      struct hda_pcm_stream *hinfo)
{
	u32 rates;
	u64 formats;
	unsigned int maxbps;
	unsigned int channels_max;
	int i;

	/* assume basic audio support (the basic audio flag is not in ELD;
	 * however, all audio capable sinks are required to support basic
	 * audio) */
	rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
		SNDRV_PCM_RATE_48000;
	formats = SNDRV_PCM_FMTBIT_S16_LE;
	maxbps = 16;
	channels_max = 2;
	for (i = 0; i < e->sad_count; i++) {
		struct cea_sad *a = &e->sad[i];
		rates |= a->rates;
		if (a->channels > channels_max)
			channels_max = a->channels;
		if (a->format == AUDIO_CODING_TYPE_LPCM) {
			if (a->sample_bits & AC_SUPPCM_BITS_20) {
				formats |= SNDRV_PCM_FMTBIT_S32_LE;
				if (maxbps < 20)
					maxbps = 20;
			}
			if (a->sample_bits & AC_SUPPCM_BITS_24) {
				formats |= SNDRV_PCM_FMTBIT_S32_LE;
				if (maxbps < 24)
					maxbps = 24;
			}
		}
	}

	/* restrict the parameters by the values the codec provides */
	hinfo->rates &= rates;
	hinfo->formats &= formats;
	hinfo->maxbps = min(hinfo->maxbps, maxbps);
	hinfo->channels_max = min(hinfo->channels_max, channels_max);
}