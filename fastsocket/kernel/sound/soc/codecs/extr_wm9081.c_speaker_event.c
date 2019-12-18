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
struct snd_soc_dapm_widget {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  WM9081_POWER_MANAGEMENT ; 
 unsigned int WM9081_SPK_ENA ; 
 unsigned int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int speaker_event(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	unsigned int reg = snd_soc_read(codec, WM9081_POWER_MANAGEMENT);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		reg |= WM9081_SPK_ENA;
		break;

	case SND_SOC_DAPM_PRE_PMD:
		reg &= ~WM9081_SPK_ENA;
		break;
	}

	snd_soc_write(codec, WM9081_POWER_MANAGEMENT, reg);

	return 0;
}