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
struct snd_soc_dapm_widget {int /*<<< orphan*/  codec; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CD ; 
 int /*<<< orphan*/  AC97_LINE ; 
 int /*<<< orphan*/  AC97_PCM ; 
 int /*<<< orphan*/  AC97_PC_BEEP ; 
 int /*<<< orphan*/  AC97_PHONE ; 
 int /*<<< orphan*/  AC97_VIDEO ; 
 int /*<<< orphan*/  HPL_MIXER ; 
 int /*<<< orphan*/  HPR_MIXER ; 
 int ac97_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mixer_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *k, int event)
{
	u16 l, r, beep, line, phone, mic, pcm, aux;

	l = ac97_read(w->codec, HPL_MIXER);
	r = ac97_read(w->codec, HPR_MIXER);
	beep = ac97_read(w->codec, AC97_PC_BEEP);
	mic = ac97_read(w->codec, AC97_VIDEO);
	phone = ac97_read(w->codec, AC97_PHONE);
	line = ac97_read(w->codec, AC97_LINE);
	pcm = ac97_read(w->codec, AC97_PCM);
	aux = ac97_read(w->codec, AC97_CD);

	if (l & 0x1 || r & 0x1)
		ac97_write(w->codec, AC97_VIDEO, mic & 0x7fff);
	else
		ac97_write(w->codec, AC97_VIDEO, mic | 0x8000);

	if (l & 0x2 || r & 0x2)
		ac97_write(w->codec, AC97_PCM, pcm & 0x7fff);
	else
		ac97_write(w->codec, AC97_PCM, pcm | 0x8000);

	if (l & 0x4 || r & 0x4)
		ac97_write(w->codec, AC97_LINE, line & 0x7fff);
	else
		ac97_write(w->codec, AC97_LINE, line | 0x8000);

	if (l & 0x8 || r & 0x8)
		ac97_write(w->codec, AC97_PHONE, phone & 0x7fff);
	else
		ac97_write(w->codec, AC97_PHONE, phone | 0x8000);

	if (l & 0x10 || r & 0x10)
		ac97_write(w->codec, AC97_CD, aux & 0x7fff);
	else
		ac97_write(w->codec, AC97_CD, aux | 0x8000);

	if (l & 0x20 || r & 0x20)
		ac97_write(w->codec, AC97_PC_BEEP, beep & 0x7fff);
	else
		ac97_write(w->codec, AC97_PC_BEEP, beep | 0x8000);

	return 0;
}