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
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 134 
#define  SND_SOC_DAIFMT_CBS_CFS 133 
#define  SND_SOC_DAIFMT_DSP_A 132 
#define  SND_SOC_DAIFMT_DSP_B 131 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 130 
#define  SND_SOC_DAIFMT_LEFT_J 129 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int WM8400_AIF_FMT_DSP ; 
 int WM8400_AIF_FMT_I2S ; 
 int WM8400_AIF_FMT_LEFTJ ; 
 int WM8400_AIF_FMT_MASK ; 
 int WM8400_AIF_FMT_RIGHTJ ; 
 int WM8400_AIF_LRCLK_INV ; 
 int WM8400_AIF_MSTR1 ; 
 int /*<<< orphan*/  WM8400_AUDIO_INTERFACE_1 ; 
 int /*<<< orphan*/  WM8400_AUDIO_INTERFACE_3 ; 
 int wm8400_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8400_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8400_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 audio1, audio3;

	audio1 = wm8400_read(codec, WM8400_AUDIO_INTERFACE_1);
	audio3 = wm8400_read(codec, WM8400_AUDIO_INTERFACE_3);

	/* set master/slave audio interface */
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		audio3 &= ~WM8400_AIF_MSTR1;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		audio3 |= WM8400_AIF_MSTR1;
		break;
	default:
		return -EINVAL;
	}

	audio1 &= ~WM8400_AIF_FMT_MASK;

	/* interface format */
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		audio1 |= WM8400_AIF_FMT_I2S;
		audio1 &= ~WM8400_AIF_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		audio1 |= WM8400_AIF_FMT_RIGHTJ;
		audio1 &= ~WM8400_AIF_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		audio1 |= WM8400_AIF_FMT_LEFTJ;
		audio1 &= ~WM8400_AIF_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		audio1 |= WM8400_AIF_FMT_DSP;
		audio1 &= ~WM8400_AIF_LRCLK_INV;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		audio1 |= WM8400_AIF_FMT_DSP | WM8400_AIF_LRCLK_INV;
		break;
	default:
		return -EINVAL;
	}

	wm8400_write(codec, WM8400_AUDIO_INTERFACE_1, audio1);
	wm8400_write(codec, WM8400_AUDIO_INTERFACE_3, audio3);
	return 0;
}