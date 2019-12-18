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
struct snd_opl3 {scalar_t__ fm_mode; int /*<<< orphan*/  (* command ) (struct snd_opl3*,unsigned short,unsigned char) ;} ;
struct snd_dm_fm_voice {int op; unsigned char voice; unsigned char harmonic; int scale_level; unsigned char volume; int attack; unsigned char decay; int sustain; unsigned char release; int feedback; unsigned char waveform; scalar_t__ right; scalar_t__ left; scalar_t__ connection; scalar_t__ kbd_scale; scalar_t__ do_sustain; scalar_t__ vibrato; scalar_t__ am; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char MAX_OPL2_VOICES ; 
 unsigned char MAX_OPL3_VOICES ; 
 int OPL3_ATTACK_MASK ; 
 unsigned char OPL3_CONNECTION_BIT ; 
 unsigned char OPL3_DECAY_MASK ; 
 int OPL3_FEEDBACK_MASK ; 
 int OPL3_KSL_MASK ; 
 unsigned char OPL3_KSR ; 
 unsigned short OPL3_LEFT ; 
 unsigned char OPL3_MULTIPLE_MASK ; 
 unsigned char OPL3_REG_AM_VIB ; 
 unsigned char OPL3_REG_ATTACK_DECAY ; 
 unsigned char OPL3_REG_FEEDBACK_CONNECTION ; 
 unsigned char OPL3_REG_KSL_LEVEL ; 
 unsigned char OPL3_REG_SUSTAIN_RELEASE ; 
 unsigned char OPL3_REG_WAVE_SELECT ; 
 unsigned char OPL3_RELEASE_MASK ; 
 unsigned short OPL3_RIGHT ; 
 int OPL3_SUSTAIN_MASK ; 
 unsigned char OPL3_SUSTAIN_ON ; 
 unsigned char OPL3_TOTAL_LEVEL_MASK ; 
 unsigned char OPL3_TREMOLO_ON ; 
 unsigned char OPL3_VIBRATO_ON ; 
 unsigned char OPL3_VOICE_TO_LEFT ; 
 unsigned char OPL3_VOICE_TO_RIGHT ; 
 unsigned char OPL3_WAVE_SELECT_MASK ; 
 scalar_t__ SNDRV_DM_FM_MODE_OPL3 ; 
 unsigned char** snd_opl3_regmap ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub2 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub3 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub4 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub5 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub6 (struct snd_opl3*,unsigned short,unsigned char) ; 

__attribute__((used)) static int snd_opl3_set_voice(struct snd_opl3 * opl3, struct snd_dm_fm_voice * voice)
{
	unsigned short reg_side;
	unsigned char op_offset;
	unsigned char voice_offset;

	unsigned short opl3_reg;
	unsigned char reg_val;

	/* Only operators 1 and 2 */
	if (voice->op > 1)
		return -EINVAL;
	/* Voices 0 -  8 in OPL2 mode */
	/* Voices 0 - 17 in OPL3 mode */
	if (voice->voice >= ((opl3->fm_mode == SNDRV_DM_FM_MODE_OPL3) ?
			     MAX_OPL3_VOICES : MAX_OPL2_VOICES))
		return -EINVAL;

	/* Get register array side and offset of voice */
	if (voice->voice < MAX_OPL2_VOICES) {
		/* Left register block for voices 0 .. 8 */
		reg_side = OPL3_LEFT;
		voice_offset = voice->voice;
	} else {
		/* Right register block for voices 9 .. 17 */
		reg_side = OPL3_RIGHT;
		voice_offset = voice->voice - MAX_OPL2_VOICES;
	}
	/* Get register offset of operator */
	op_offset = snd_opl3_regmap[voice_offset][voice->op];

	reg_val = 0x00;
	/* Set amplitude modulation (tremolo) effect */
	if (voice->am)
		reg_val |= OPL3_TREMOLO_ON;
	/* Set vibrato effect */
	if (voice->vibrato)
		reg_val |= OPL3_VIBRATO_ON;
	/* Set sustaining sound phase */
	if (voice->do_sustain)
		reg_val |= OPL3_SUSTAIN_ON;
	/* Set keyboard scaling bit */ 
	if (voice->kbd_scale)
		reg_val |= OPL3_KSR;
	/* Set harmonic or frequency multiplier */
	reg_val |= voice->harmonic & OPL3_MULTIPLE_MASK;

	/* Set OPL3 AM_VIB register of requested voice/operator */ 
	opl3_reg = reg_side | (OPL3_REG_AM_VIB + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set decreasing volume of higher notes */
	reg_val = (voice->scale_level << 6) & OPL3_KSL_MASK;
	/* Set output volume */
	reg_val |= ~voice->volume & OPL3_TOTAL_LEVEL_MASK;

	/* Set OPL3 KSL_LEVEL register of requested voice/operator */ 
	opl3_reg = reg_side | (OPL3_REG_KSL_LEVEL + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set attack phase level */
	reg_val = (voice->attack << 4) & OPL3_ATTACK_MASK;
	/* Set decay phase level */
	reg_val |= voice->decay & OPL3_DECAY_MASK;

	/* Set OPL3 ATTACK_DECAY register of requested voice/operator */ 
	opl3_reg = reg_side | (OPL3_REG_ATTACK_DECAY + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set sustain phase level */
	reg_val = (voice->sustain << 4) & OPL3_SUSTAIN_MASK;
	/* Set release phase level */
	reg_val |= voice->release & OPL3_RELEASE_MASK;

	/* Set OPL3 SUSTAIN_RELEASE register of requested voice/operator */ 
	opl3_reg = reg_side | (OPL3_REG_SUSTAIN_RELEASE + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set inter-operator feedback */
	reg_val = (voice->feedback << 1) & OPL3_FEEDBACK_MASK;
	/* Set inter-operator connection */
	if (voice->connection)
		reg_val |= OPL3_CONNECTION_BIT;
	/* OPL-3 only */
	if (opl3->fm_mode == SNDRV_DM_FM_MODE_OPL3) {
		if (voice->left)
			reg_val |= OPL3_VOICE_TO_LEFT;
		if (voice->right)
			reg_val |= OPL3_VOICE_TO_RIGHT;
	}
	/* Feedback/connection bits are applicable to voice */
	opl3_reg = reg_side | (OPL3_REG_FEEDBACK_CONNECTION + voice_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Select waveform */
	reg_val = voice->waveform & OPL3_WAVE_SELECT_MASK;
	opl3_reg = reg_side | (OPL3_REG_WAVE_SELECT + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	return 0;
}