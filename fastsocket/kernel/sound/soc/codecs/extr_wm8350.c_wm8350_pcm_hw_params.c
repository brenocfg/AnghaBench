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
typedef  int u16 ;
struct wm8350 {int dummy; } ;
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {struct wm8350* control_data; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S20_3LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int WM8350_AIF_WL_MASK ; 
 int /*<<< orphan*/  WM8350_AI_FORMATING ; 
 int /*<<< orphan*/  WM8350_DAC_MUTE_VOLUME ; 
 int /*<<< orphan*/  WM8350_DAC_SB_FILT ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wm8350_codec_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_codec_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_pcm_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *codec_dai)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct wm8350 *wm8350 = codec->control_data;
	u16 iface = wm8350_codec_read(codec, WM8350_AI_FORMATING) &
	    ~WM8350_AIF_WL_MASK;

	/* bit size */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		iface |= 0x1 << 10;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		iface |= 0x2 << 10;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		iface |= 0x3 << 10;
		break;
	}

	wm8350_codec_write(codec, WM8350_AI_FORMATING, iface);

	/* The sloping stopband filter is recommended for use with
	 * lower sample rates to improve performance.
	 */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		if (params_rate(params) < 24000)
			wm8350_set_bits(wm8350, WM8350_DAC_MUTE_VOLUME,
					WM8350_DAC_SB_FILT);
		else
			wm8350_clear_bits(wm8350, WM8350_DAC_MUTE_VOLUME,
					  WM8350_DAC_SB_FILT);
	}

	return 0;
}