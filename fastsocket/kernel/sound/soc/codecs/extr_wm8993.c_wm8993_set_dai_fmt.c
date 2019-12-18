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
struct wm8993_priv {int master; } ;
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {struct wm8993_priv* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 140 
#define  SND_SOC_DAIFMT_CBM_CFS 139 
#define  SND_SOC_DAIFMT_CBS_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 unsigned int WM8993_AIF_BCLK_INV ; 
 unsigned int WM8993_AIF_FMT_MASK ; 
 unsigned int WM8993_AIF_LRCLK_INV ; 
 int /*<<< orphan*/  WM8993_AUDIO_INTERFACE_1 ; 
 int /*<<< orphan*/  WM8993_AUDIO_INTERFACE_4 ; 
 unsigned int WM8993_BCLK_DIR ; 
 unsigned int WM8993_LRCLK_DIR ; 
 unsigned int wm8993_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8993_write (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int wm8993_set_dai_fmt(struct snd_soc_dai *dai,
			      unsigned int fmt)
{
	struct snd_soc_codec *codec = dai->codec;
	struct wm8993_priv *wm8993 = codec->private_data;
	unsigned int aif1 = wm8993_read(codec, WM8993_AUDIO_INTERFACE_1);
	unsigned int aif4 = wm8993_read(codec, WM8993_AUDIO_INTERFACE_4);

	aif1 &= ~(WM8993_BCLK_DIR | WM8993_AIF_BCLK_INV |
		  WM8993_AIF_LRCLK_INV | WM8993_AIF_FMT_MASK);
	aif4 &= ~WM8993_LRCLK_DIR;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		wm8993->master = 0;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		aif4 |= WM8993_LRCLK_DIR;
		wm8993->master = 1;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		aif1 |= WM8993_BCLK_DIR;
		wm8993->master = 1;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		aif1 |= WM8993_BCLK_DIR;
		aif4 |= WM8993_LRCLK_DIR;
		wm8993->master = 1;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_B:
		aif1 |= WM8993_AIF_LRCLK_INV;
	case SND_SOC_DAIFMT_DSP_A:
		aif1 |= 0x18;
		break;
	case SND_SOC_DAIFMT_I2S:
		aif1 |= 0x10;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		aif1 |= 0x8;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		/* frame inversion not valid for DSP modes */
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif1 |= WM8993_AIF_BCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;

	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_RIGHT_J:
	case SND_SOC_DAIFMT_LEFT_J:
		switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
		case SND_SOC_DAIFMT_NB_NF:
			break;
		case SND_SOC_DAIFMT_IB_IF:
			aif1 |= WM8993_AIF_BCLK_INV | WM8993_AIF_LRCLK_INV;
			break;
		case SND_SOC_DAIFMT_IB_NF:
			aif1 |= WM8993_AIF_BCLK_INV;
			break;
		case SND_SOC_DAIFMT_NB_IF:
			aif1 |= WM8993_AIF_LRCLK_INV;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	wm8993_write(codec, WM8993_AUDIO_INTERFACE_1, aif1);
	wm8993_write(codec, WM8993_AUDIO_INTERFACE_4, aif4);

	return 0;
}