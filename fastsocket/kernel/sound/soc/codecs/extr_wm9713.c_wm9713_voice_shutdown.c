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
struct snd_soc_dapm_widget {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_MID ; 
 int /*<<< orphan*/  AC97_HANDSET_RATE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SND_SOC_DAPM_PRE_PMD ; 
 int ac97_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm9713_voice_shutdown(struct snd_soc_dapm_widget *w,
				 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_codec *codec = w->codec;
	u16 status, rate;

	BUG_ON(event != SND_SOC_DAPM_PRE_PMD);

	/* Gracefully shut down the voice interface. */
	status = ac97_read(codec, AC97_EXTENDED_MID) | 0x1000;
	rate = ac97_read(codec, AC97_HANDSET_RATE) & 0xF0FF;
	ac97_write(codec, AC97_HANDSET_RATE, rate | 0x0200);
	schedule_timeout_interruptible(msecs_to_jiffies(1));
	ac97_write(codec, AC97_HANDSET_RATE, rate | 0x0F00);
	ac97_write(codec, AC97_EXTENDED_MID, status);

	return 0;
}