#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_midi_channel {int drum_channel; } ;
struct TYPE_2__ {int max_channels; struct snd_midi_channel* channels; } ;
struct snd_emux_port {int* ctrls; int drum_flags; TYPE_1__ chset; } ;

/* Variables and functions */
 size_t EMUX_MD_DEF_BANK ; 
 size_t EMUX_MD_DEF_DRUM ; 
 size_t EMUX_MD_REALTIME_PAN ; 
 int /*<<< orphan*/  snd_emux_clear_effect (struct snd_emux_port*) ; 
 int /*<<< orphan*/  snd_emux_sounds_off_all (struct snd_emux_port*) ; 
 int /*<<< orphan*/  snd_midi_channel_set_clear (TYPE_1__*) ; 

void
snd_emux_reset_port(struct snd_emux_port *port)
{
	int i;

	/* stop all sounds */
	snd_emux_sounds_off_all(port);

	snd_midi_channel_set_clear(&port->chset);

#ifdef SNDRV_EMUX_USE_RAW_EFFECT
	snd_emux_clear_effect(port);
#endif

	/* set port specific control parameters */
	port->ctrls[EMUX_MD_DEF_BANK] = 0;
	port->ctrls[EMUX_MD_DEF_DRUM] = 0;
	port->ctrls[EMUX_MD_REALTIME_PAN] = 1;

	for (i = 0; i < port->chset.max_channels; i++) {
		struct snd_midi_channel *chan = port->chset.channels + i;
		chan->drum_channel = ((port->drum_flags >> i) & 1) ? 1 : 0;
	}
}