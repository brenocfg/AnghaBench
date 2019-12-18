#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ running; } ;
struct TYPE_4__ {scalar_t__ running; } ;
struct snd_pmac {int* freq_table; int /*<<< orphan*/  reg_lock; TYPE_1__ capture; TYPE_2__ playback; struct pmac_beep* beep; } ;
struct pmac_beep {int running; int hz; short volume; short volume_play; int nsamples; short* buf; int /*<<< orphan*/  addr; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int BEEP_BUFLEN ; 
 int /*<<< orphan*/  BEEP_SRATE ; 
 unsigned int EV_SND ; 
#define  SND_BELL 129 
#define  SND_TONE 128 
 short* beep_wform ; 
 struct snd_pmac* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  snd_pmac_beep_dma_start (struct snd_pmac*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pmac_beep_stop (struct snd_pmac*) ; 
 int snd_pmac_rate_index (struct snd_pmac*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_pmac_beep_event(struct input_dev *dev, unsigned int type,
			       unsigned int code, int hz)
{
	struct snd_pmac *chip;
	struct pmac_beep *beep;
	unsigned long flags;
	int beep_speed = 0;
	int srate;
	int period, ncycles, nsamples;
	int i, j, f;
	short *p;

	if (type != EV_SND)
		return -1;

	switch (code) {
	case SND_BELL: if (hz) hz = 1000;
	case SND_TONE: break;
	default: return -1;
	}

	chip = input_get_drvdata(dev);
	if (! chip || (beep = chip->beep) == NULL)
		return -1;

	if (! hz) {
		spin_lock_irqsave(&chip->reg_lock, flags);
		if (beep->running)
			snd_pmac_beep_stop(chip);
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		return 0;
	}

	beep_speed = snd_pmac_rate_index(chip, &chip->playback, BEEP_SRATE);
	srate = chip->freq_table[beep_speed];

	if (hz <= srate / BEEP_BUFLEN || hz > srate / 2)
		hz = 1000;

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (chip->playback.running || chip->capture.running || beep->running) {
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		return 0;
	}
	beep->running = 1;
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	if (hz == beep->hz && beep->volume == beep->volume_play) {
		nsamples = beep->nsamples;
	} else {
		period = srate * 256 / hz;	/* fixed point */
		ncycles = BEEP_BUFLEN * 256 / period;
		nsamples = (period * ncycles) >> 8;
		f = ncycles * 65536 / nsamples;
		j = 0;
		p = beep->buf;
		for (i = 0; i < nsamples; ++i, p += 2) {
			p[0] = p[1] = beep_wform[j >> 8] * beep->volume;
			j = (j + f) & 0xffff;
		}
		beep->hz = hz;
		beep->volume_play = beep->volume;
		beep->nsamples = nsamples;
	}

	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_pmac_beep_dma_start(chip, beep->nsamples * 4, beep->addr, beep_speed);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return 0;
}