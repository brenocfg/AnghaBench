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
struct snd_midi_channel {int dummy; } ;
struct snd_emux_voice {int key; scalar_t__ ontime; int /*<<< orphan*/  state; struct snd_midi_channel* chan; } ;
struct snd_emux_port {struct snd_emux* emu; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct snd_emux_voice*) ;} ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct snd_emux {int max_voices; int timer_active; int /*<<< orphan*/  voice_lock; TYPE_1__ ops; TYPE_2__ tlist; struct snd_emux_voice* voices; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_EMUX_ST_PENDING ; 
 int /*<<< orphan*/  SNDRV_EMUX_ST_RELEASED ; 
 scalar_t__ STATE_IS_PLAYING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_emux_voice*) ; 

void
snd_emux_note_off(void *p, int note, int vel, struct snd_midi_channel *chan)
{
	int ch;
	struct snd_emux *emu;
	struct snd_emux_voice *vp;
	unsigned long flags;
	struct snd_emux_port *port;

	port = p;
	if (snd_BUG_ON(!port || !chan))
		return;

	emu = port->emu;
	if (snd_BUG_ON(!emu || !emu->ops.release))
		return;

	spin_lock_irqsave(&emu->voice_lock, flags);
	for (ch = 0; ch < emu->max_voices; ch++) {
		vp = &emu->voices[ch];
		if (STATE_IS_PLAYING(vp->state) &&
		    vp->chan == chan && vp->key == note) {
			vp->state = SNDRV_EMUX_ST_RELEASED;
			if (vp->ontime == jiffies) {
				/* if note-off is sent too shortly after
				 * note-on, emuX engine cannot produce the sound
				 * correctly.  so we'll release this note
				 * a bit later via timer callback.
				 */
				vp->state = SNDRV_EMUX_ST_PENDING;
				if (! emu->timer_active) {
					emu->tlist.expires = jiffies + 1;
					add_timer(&emu->tlist);
					emu->timer_active = 1;
				}
			} else
				/* ok now release the note */
				emu->ops.release(vp);
		}
	}
	spin_unlock_irqrestore(&emu->voice_lock, flags);
}