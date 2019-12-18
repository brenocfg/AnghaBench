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
struct TYPE_4__ {scalar_t__ exclusiveClass; } ;
struct snd_sf_zone {TYPE_2__* sample; TYPE_1__ v; } ;
struct snd_midi_channel {struct snd_emux_effect_table* private; } ;
struct snd_emux_voice {scalar_t__ ch; scalar_t__ state; int key; int note; int velocity; int /*<<< orphan*/  ontime; struct snd_midi_channel* chan; int /*<<< orphan*/ * block; struct snd_sf_zone* zone; struct snd_emux_port* port; scalar_t__ time; } ;
struct snd_emux_port {scalar_t__ port_mode; struct snd_emux* emu; } ;
struct snd_emux_effect_table {scalar_t__* flag; } ;
struct TYPE_6__ {scalar_t__ (* prepare ) (struct snd_emux_voice*) ;int /*<<< orphan*/  (* trigger ) (struct snd_emux_voice*) ;int /*<<< orphan*/  (* terminate ) (struct snd_emux_voice*) ;struct snd_emux_voice* (* get_voice ) (struct snd_emux*,struct snd_emux_port*) ;} ;
struct snd_emux {int max_voices; int /*<<< orphan*/  voice_lock; TYPE_3__ ops; struct snd_emux_voice* voices; int /*<<< orphan*/  use_time; } ;
struct TYPE_5__ {int /*<<< orphan*/ * block; } ;

/* Variables and functions */
 size_t EMUX_FX_COARSE_SAMPLE_START ; 
 size_t EMUX_FX_SAMPLE_START ; 
 int SNDRV_EMUX_MAX_MULTI_VOICES ; 
 scalar_t__ SNDRV_EMUX_PORT_MODE_OSS_SYNTH ; 
 scalar_t__ SNDRV_EMUX_ST_OFF ; 
 scalar_t__ SNDRV_EMUX_ST_ON ; 
 scalar_t__ SNDRV_EMUX_ST_STANDBY ; 
 scalar_t__ STATE_IS_PLAYING (scalar_t__) ; 
 int /*<<< orphan*/  exclusive_note_off (struct snd_emux*,struct snd_emux_port*,scalar_t__) ; 
 int get_zone (struct snd_emux*,struct snd_emux_port*,int*,int,struct snd_midi_channel*,struct snd_sf_zone**) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  setup_voice (struct snd_emux_voice*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct snd_emux_voice* stub1 (struct snd_emux*,struct snd_emux_port*) ; 
 int /*<<< orphan*/  stub2 (struct snd_emux_voice*) ; 
 scalar_t__ stub3 (struct snd_emux_voice*) ; 
 int /*<<< orphan*/  stub4 (struct snd_emux_voice*) ; 
 int /*<<< orphan*/  terminate_note1 (struct snd_emux*,int,struct snd_midi_channel*,int /*<<< orphan*/ ) ; 

void
snd_emux_note_on(void *p, int note, int vel, struct snd_midi_channel *chan)
{
	struct snd_emux *emu;
	int i, key, nvoices;
	struct snd_emux_voice *vp;
	struct snd_sf_zone *table[SNDRV_EMUX_MAX_MULTI_VOICES];
	unsigned long flags;
	struct snd_emux_port *port;

	port = p;
	if (snd_BUG_ON(!port || !chan))
		return;

	emu = port->emu;
	if (snd_BUG_ON(!emu || !emu->ops.get_voice || !emu->ops.trigger))
		return;

	key = note; /* remember the original note */
	nvoices = get_zone(emu, port, &note, vel, chan, table);
	if (! nvoices)
		return;

	/* exclusive note off */
	for (i = 0; i < nvoices; i++) {
		struct snd_sf_zone *zp = table[i];
		if (zp && zp->v.exclusiveClass)
			exclusive_note_off(emu, port, zp->v.exclusiveClass);
	}

#if 0 // seems not necessary
	/* Turn off the same note on the same channel. */
	terminate_note1(emu, key, chan, 0);
#endif

	spin_lock_irqsave(&emu->voice_lock, flags);
	for (i = 0; i < nvoices; i++) {

		/* set up each voice parameter */
		/* at this stage, we don't trigger the voice yet. */

		if (table[i] == NULL)
			continue;

		vp = emu->ops.get_voice(emu, port);
		if (vp == NULL || vp->ch < 0)
			continue;
		if (STATE_IS_PLAYING(vp->state))
			emu->ops.terminate(vp);

		vp->time = emu->use_time++;
		vp->chan = chan;
		vp->port = port;
		vp->key = key;
		vp->note = note;
		vp->velocity = vel;
		vp->zone = table[i];
		if (vp->zone->sample)
			vp->block = vp->zone->sample->block;
		else
			vp->block = NULL;

		setup_voice(vp);

		vp->state = SNDRV_EMUX_ST_STANDBY;
		if (emu->ops.prepare) {
			vp->state = SNDRV_EMUX_ST_OFF;
			if (emu->ops.prepare(vp) >= 0)
				vp->state = SNDRV_EMUX_ST_STANDBY;
		}
	}

	/* start envelope now */
	for (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		if (vp->state == SNDRV_EMUX_ST_STANDBY &&
		    vp->chan == chan) {
			emu->ops.trigger(vp);
			vp->state = SNDRV_EMUX_ST_ON;
			vp->ontime = jiffies; /* remember the trigger timing */
		}
	}
	spin_unlock_irqrestore(&emu->voice_lock, flags);

#ifdef SNDRV_EMUX_USE_RAW_EFFECT
	if (port->port_mode == SNDRV_EMUX_PORT_MODE_OSS_SYNTH) {
		/* clear voice position for the next note on this channel */
		struct snd_emux_effect_table *fx = chan->private;
		if (fx) {
			fx->flag[EMUX_FX_SAMPLE_START] = 0;
			fx->flag[EMUX_FX_COARSE_SAMPLE_START] = 0;
		}
	}
#endif
}