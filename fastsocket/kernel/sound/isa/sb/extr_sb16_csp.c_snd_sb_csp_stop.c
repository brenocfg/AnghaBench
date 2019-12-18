#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_sb_csp {int running; TYPE_1__* chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  mixer_lock; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 scalar_t__ SB_DSP4_PCM_DEV ; 
 int SNDRV_SB_CSP_ST_PAUSED ; 
 int SNDRV_SB_CSP_ST_QSOUND ; 
 int SNDRV_SB_CSP_ST_RUNNING ; 
 int /*<<< orphan*/  set_codec_parameter (TYPE_1__*,int,int) ; 
 int set_mode_register (TYPE_1__*,int) ; 
 unsigned char snd_sbmixer_read (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  snd_sbmixer_write (TYPE_1__*,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb_csp_stop(struct snd_sb_csp * p)
{
	int result;
	unsigned char mixL, mixR;
	unsigned long flags;

	if (!(p->running & SNDRV_SB_CSP_ST_RUNNING))
		return 0;

	/* Mute PCM volume */
	spin_lock_irqsave(&p->chip->mixer_lock, flags);
	mixL = snd_sbmixer_read(p->chip, SB_DSP4_PCM_DEV);
	mixR = snd_sbmixer_read(p->chip, SB_DSP4_PCM_DEV + 1);
	snd_sbmixer_write(p->chip, SB_DSP4_PCM_DEV, mixL & 0x7);
	snd_sbmixer_write(p->chip, SB_DSP4_PCM_DEV + 1, mixR & 0x7);

	spin_lock(&p->chip->reg_lock);
	if (p->running & SNDRV_SB_CSP_ST_QSOUND) {
		set_codec_parameter(p->chip, 0xe0, 0x01);
		/* disable QSound decoder */
		set_codec_parameter(p->chip, 0x00, 0x00);
		set_codec_parameter(p->chip, 0x01, 0x00);

		p->running &= ~SNDRV_SB_CSP_ST_QSOUND;
	}
	result = set_mode_register(p->chip, 0xc0);	/* c0 = STOP */
	spin_unlock(&p->chip->reg_lock);

	/* restore PCM volume */
	snd_sbmixer_write(p->chip, SB_DSP4_PCM_DEV, mixL);
	snd_sbmixer_write(p->chip, SB_DSP4_PCM_DEV + 1, mixR);
	spin_unlock_irqrestore(&p->chip->mixer_lock, flags);

	if (!(result))
		p->running &= ~(SNDRV_SB_CSP_ST_PAUSED | SNDRV_SB_CSP_ST_RUNNING);
	return result;
}