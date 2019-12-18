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
struct snd_midi_channel {int* control; struct snd_emux_effect_table* private; } ;
struct TYPE_5__ {int cutoff; int /*<<< orphan*/  volatkhld; } ;
struct TYPE_6__ {int amplitude; TYPE_2__ parm; scalar_t__ attenuation; } ;
struct snd_emux_voice {int velocity; int avol; int acutoff; TYPE_3__ reg; struct snd_emux_port* port; struct snd_midi_channel* chan; } ;
struct TYPE_4__ {int gs_master_volume; } ;
struct snd_emux_port {scalar_t__ port_mode; scalar_t__ volume_atten; TYPE_1__ chset; } ;
struct snd_emux_effect_table {scalar_t__* val; } ;

/* Variables and functions */
 size_t EMUX_FX_ATTEN ; 
 int /*<<< orphan*/  LIMITMAX (int,int) ; 
 int /*<<< orphan*/  LIMITVALUE (int,int /*<<< orphan*/ ,int) ; 
 int LO_BYTE (int /*<<< orphan*/ ) ; 
 size_t MIDI_CTL_MSB_EXPRESSION ; 
 size_t MIDI_CTL_MSB_MAIN_VOLUME ; 
 int /*<<< orphan*/  SF_IS_DRUM_BANK (int /*<<< orphan*/ ) ; 
 scalar_t__ SNDRV_EMUX_PORT_MODE_OSS_SYNTH ; 
 int* expressiontab ; 
 int /*<<< orphan*/  get_bank (struct snd_emux_port*,struct snd_midi_channel*) ; 
 int* snd_sf_vol_table ; 
 int* voltab1 ; 
 int* voltab2 ; 

__attribute__((used)) static int
calc_volume(struct snd_emux_voice *vp)
{
	int vol;
	int main_vol, expression_vol, master_vol;
	struct snd_midi_channel *chan = vp->chan;
	struct snd_emux_port *port = vp->port;

	expression_vol = chan->control[MIDI_CTL_MSB_EXPRESSION];
	LIMITMAX(vp->velocity, 127);
	LIMITVALUE(expression_vol, 0, 127);
	if (port->port_mode == SNDRV_EMUX_PORT_MODE_OSS_SYNTH) {
		/* 0 - 127 */
		main_vol = chan->control[MIDI_CTL_MSB_MAIN_VOLUME];
		vol = (vp->velocity * main_vol * expression_vol) / (127*127);
		vol = vol * vp->reg.amplitude / 127;

		LIMITVALUE(vol, 0, 127);

		/* calc to attenuation */
		vol = snd_sf_vol_table[vol];

	} else {
		main_vol = chan->control[MIDI_CTL_MSB_MAIN_VOLUME] * vp->reg.amplitude / 127;
		LIMITVALUE(main_vol, 0, 127);

		vol = voltab1[main_vol] + voltab2[vp->velocity];
		vol = (vol * 8) / 3;
		vol += vp->reg.attenuation;
		vol += ((0x100 - vol) * expressiontab[expression_vol])/128;
	}

	master_vol = port->chset.gs_master_volume;
	LIMITVALUE(master_vol, 0, 127);
	vol += snd_sf_vol_table[master_vol];
	vol += port->volume_atten;

#ifdef SNDRV_EMUX_USE_RAW_EFFECT
	if (chan->private) {
		struct snd_emux_effect_table *fx = chan->private;
		vol += fx->val[EMUX_FX_ATTEN];
	}
#endif

	LIMITVALUE(vol, 0, 255);
	if (vp->avol == vol)
		return 0; /* value unchanged */

	vp->avol = vol;
	if (!SF_IS_DRUM_BANK(get_bank(port, chan))
	    && LO_BYTE(vp->reg.parm.volatkhld) < 0x7d) {
		int atten;
		if (vp->velocity < 70)
			atten = 70;
		else
			atten = vp->velocity;
		vp->acutoff = (atten * vp->reg.parm.cutoff + 0xa0) >> 7;
	} else {
		vp->acutoff = vp->reg.parm.cutoff;
	}

	return 1; /* value changed */
}