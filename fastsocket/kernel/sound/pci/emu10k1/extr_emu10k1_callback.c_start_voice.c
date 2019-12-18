#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_midi_channel {scalar_t__* control; } ;
struct TYPE_5__ {unsigned int moddelay; unsigned int modatkhld; unsigned int moddcysus; unsigned int voldelay; unsigned int volatkhld; unsigned int pefe; unsigned int lfo1delay; unsigned int lfo2delay; unsigned int tremfrq; unsigned int reverb; unsigned int chorus; unsigned int filterQ; } ;
struct TYPE_6__ {unsigned int start; unsigned int end; unsigned int loopstart; unsigned int loopend; int sample_mode; TYPE_2__ parm; } ;
struct snd_emux_voice {int ch; unsigned int apitch; unsigned int ftarget; scalar_t__ vtarget; TYPE_3__ reg; struct snd_midi_channel* chan; scalar_t__ avol; scalar_t__ acutoff; scalar_t__ block; struct snd_emu10k1* hw; } ;
struct snd_emu10k1_memblk {int /*<<< orphan*/  map_locked; } ;
struct TYPE_4__ {int addr; } ;
struct snd_emu10k1 {TYPE_1__ silent_page; scalar_t__ audigy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATKHLDM ; 
 int /*<<< orphan*/  ATKHLDV ; 
 int /*<<< orphan*/  A_FXRT1 ; 
 int /*<<< orphan*/  CCCA ; 
 unsigned int CCCA_8BITSELECT ; 
 unsigned int CCCA_INTERPROM_0 ; 
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CDE ; 
 int /*<<< orphan*/  CDF ; 
 int /*<<< orphan*/  CPF ; 
 int /*<<< orphan*/  CVCF ; 
 int /*<<< orphan*/  DCYSUSM ; 
 int /*<<< orphan*/  DCYSUSV ; 
 int /*<<< orphan*/  DSL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ENVVAL ; 
 int /*<<< orphan*/  ENVVOL ; 
 int FXBUS_MIDI_CHORUS ; 
 int FXBUS_MIDI_LEFT ; 
 int FXBUS_MIDI_REVERB ; 
 int FXBUS_MIDI_RIGHT ; 
 int /*<<< orphan*/  FXRT ; 
 int /*<<< orphan*/  IFATN ; 
 int /*<<< orphan*/  IP ; 
 int /*<<< orphan*/  LFOVAL1 ; 
 int /*<<< orphan*/  LFOVAL2 ; 
 int /*<<< orphan*/  LIMITMAX (unsigned int,int) ; 
 int /*<<< orphan*/  MAPA ; 
 int /*<<< orphan*/  MAPB ; 
 int MAP_PTI_MASK ; 
 size_t MIDI_CTL_E1_REVERB_DEPTH ; 
 size_t MIDI_CTL_E3_CHORUS_DEPTH ; 
 int /*<<< orphan*/  PEFE ; 
 int /*<<< orphan*/  PSST ; 
 int /*<<< orphan*/  PTRX ; 
 int SNDRV_SFNT_SAMPLE_8BITS ; 
 int /*<<< orphan*/  TREMFRQ ; 
 int /*<<< orphan*/  VTFT ; 
 int /*<<< orphan*/  Z1 ; 
 int /*<<< orphan*/  Z2 ; 
 int /*<<< orphan*/  set_fm2frq2 (struct snd_emu10k1*,struct snd_emux_voice*) ; 
 int /*<<< orphan*/  set_fmmod (struct snd_emu10k1*,struct snd_emux_voice*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 scalar_t__ snd_emu10k1_memblk_map (struct snd_emu10k1*,struct snd_emu10k1_memblk*) ; 
 int snd_emu10k1_memblk_offset (struct snd_emu10k1_memblk*) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int
start_voice(struct snd_emux_voice *vp)
{
	unsigned int temp;
	int ch;
	unsigned int addr, mapped_offset;
	struct snd_midi_channel *chan;
	struct snd_emu10k1 *hw;
	struct snd_emu10k1_memblk *emem;
	
	hw = vp->hw;
	ch = vp->ch;
	if (snd_BUG_ON(ch < 0))
		return -EINVAL;
	chan = vp->chan;

	emem = (struct snd_emu10k1_memblk *)vp->block;
	if (emem == NULL)
		return -EINVAL;
	emem->map_locked++;
	if (snd_emu10k1_memblk_map(hw, emem) < 0) {
		/* printk(KERN_ERR "emu: cannot map!\n"); */
		return -ENOMEM;
	}
	mapped_offset = snd_emu10k1_memblk_offset(emem) >> 1;
	vp->reg.start += mapped_offset;
	vp->reg.end += mapped_offset;
	vp->reg.loopstart += mapped_offset;
	vp->reg.loopend += mapped_offset;

	/* set channel routing */
	/* A = left(0), B = right(1), C = reverb(c), D = chorus(d) */
	if (hw->audigy) {
		temp = FXBUS_MIDI_LEFT | (FXBUS_MIDI_RIGHT << 8) | 
			(FXBUS_MIDI_REVERB << 16) | (FXBUS_MIDI_CHORUS << 24);
		snd_emu10k1_ptr_write(hw, A_FXRT1, ch, temp);
	} else {
		temp = (FXBUS_MIDI_LEFT << 16) | (FXBUS_MIDI_RIGHT << 20) | 
			(FXBUS_MIDI_REVERB << 24) | (FXBUS_MIDI_CHORUS << 28);
		snd_emu10k1_ptr_write(hw, FXRT, ch, temp);
	}

	/* channel to be silent and idle */
	snd_emu10k1_ptr_write(hw, DCYSUSV, ch, 0x0000);
	snd_emu10k1_ptr_write(hw, VTFT, ch, 0x0000FFFF);
	snd_emu10k1_ptr_write(hw, CVCF, ch, 0x0000FFFF);
	snd_emu10k1_ptr_write(hw, PTRX, ch, 0);
	snd_emu10k1_ptr_write(hw, CPF, ch, 0);

	/* set pitch offset */
	snd_emu10k1_ptr_write(hw, IP, vp->ch, vp->apitch);

	/* set envelope parameters */
	snd_emu10k1_ptr_write(hw, ENVVAL, ch, vp->reg.parm.moddelay);
	snd_emu10k1_ptr_write(hw, ATKHLDM, ch, vp->reg.parm.modatkhld);
	snd_emu10k1_ptr_write(hw, DCYSUSM, ch, vp->reg.parm.moddcysus);
	snd_emu10k1_ptr_write(hw, ENVVOL, ch, vp->reg.parm.voldelay);
	snd_emu10k1_ptr_write(hw, ATKHLDV, ch, vp->reg.parm.volatkhld);
	/* decay/sustain parameter for volume envelope is used
	   for triggerg the voice */

	/* cutoff and volume */
	temp = (unsigned int)vp->acutoff << 8 | (unsigned char)vp->avol;
	snd_emu10k1_ptr_write(hw, IFATN, vp->ch, temp);

	/* modulation envelope heights */
	snd_emu10k1_ptr_write(hw, PEFE, ch, vp->reg.parm.pefe);

	/* lfo1/2 delay */
	snd_emu10k1_ptr_write(hw, LFOVAL1, ch, vp->reg.parm.lfo1delay);
	snd_emu10k1_ptr_write(hw, LFOVAL2, ch, vp->reg.parm.lfo2delay);

	/* lfo1 pitch & cutoff shift */
	set_fmmod(hw, vp);
	/* lfo1 volume & freq */
	snd_emu10k1_ptr_write(hw, TREMFRQ, vp->ch, vp->reg.parm.tremfrq);
	/* lfo2 pitch & freq */
	set_fm2frq2(hw, vp);

	/* reverb and loop start (reverb 8bit, MSB) */
	temp = vp->reg.parm.reverb;
	temp += (int)vp->chan->control[MIDI_CTL_E1_REVERB_DEPTH] * 9 / 10;
	LIMITMAX(temp, 255);
	addr = vp->reg.loopstart;
	snd_emu10k1_ptr_write(hw, PSST, vp->ch, (temp << 24) | addr);

	/* chorus & loop end (chorus 8bit, MSB) */
	addr = vp->reg.loopend;
	temp = vp->reg.parm.chorus;
	temp += (int)chan->control[MIDI_CTL_E3_CHORUS_DEPTH] * 9 / 10;
	LIMITMAX(temp, 255);
	temp = (temp <<24) | addr;
	snd_emu10k1_ptr_write(hw, DSL, ch, temp);

	/* clear filter delay memory */
	snd_emu10k1_ptr_write(hw, Z1, ch, 0);
	snd_emu10k1_ptr_write(hw, Z2, ch, 0);

	/* invalidate maps */
	temp = (hw->silent_page.addr << 1) | MAP_PTI_MASK;
	snd_emu10k1_ptr_write(hw, MAPA, ch, temp);
	snd_emu10k1_ptr_write(hw, MAPB, ch, temp);
#if 0
	/* cache */
	{
		unsigned int val, sample;
		val = 32;
		if (vp->reg.sample_mode & SNDRV_SFNT_SAMPLE_8BITS)
			sample = 0x80808080;
		else {
			sample = 0;
			val *= 2;
		}

		/* cache */
		snd_emu10k1_ptr_write(hw, CCR, ch, 0x1c << 16);
		snd_emu10k1_ptr_write(hw, CDE, ch, sample);
		snd_emu10k1_ptr_write(hw, CDF, ch, sample);

		/* invalidate maps */
		temp = ((unsigned int)hw->silent_page.addr << 1) | MAP_PTI_MASK;
		snd_emu10k1_ptr_write(hw, MAPA, ch, temp);
		snd_emu10k1_ptr_write(hw, MAPB, ch, temp);
		
		/* fill cache */
		val -= 4;
		val <<= 25;
		val |= 0x1c << 16;
		snd_emu10k1_ptr_write(hw, CCR, ch, val);
	}
#endif

	/* Q & current address (Q 4bit value, MSB) */
	addr = vp->reg.start;
	temp = vp->reg.parm.filterQ;
	temp = (temp<<28) | addr;
	if (vp->apitch < 0xe400)
		temp |= CCCA_INTERPROM_0;
	else {
		unsigned int shift = (vp->apitch - 0xe000) >> 10;
		temp |= shift << 25;
	}
	if (vp->reg.sample_mode & SNDRV_SFNT_SAMPLE_8BITS)
		temp |= CCCA_8BITSELECT;
	snd_emu10k1_ptr_write(hw, CCCA, ch, temp);

	/* reset volume */
	temp = (unsigned int)vp->vtarget << 16;
	snd_emu10k1_ptr_write(hw, VTFT, ch, temp | vp->ftarget);
	snd_emu10k1_ptr_write(hw, CVCF, ch, temp | 0xff00);
	return 0;
}