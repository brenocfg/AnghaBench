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
struct snd_midi_channel_set {int dummy; } ;
struct snd_midi_channel {int* control; } ;
struct TYPE_2__ {scalar_t__ midi_mode; } ;
struct snd_emux_port {TYPE_1__ chset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMUX_FX_FLAG_ADD ; 
 int /*<<< orphan*/  EMUX_FX_FLAG_SET ; 
 size_t MIDI_CTL_LSB_DATA_ENTRY ; 
 size_t MIDI_CTL_MSB_DATA_ENTRY ; 
 size_t MIDI_CTL_NONREG_PARM_NUM_LSB ; 
 size_t MIDI_CTL_NONREG_PARM_NUM_MSB ; 
 scalar_t__ SNDRV_MIDI_MODE_GS ; 
 int /*<<< orphan*/  awe_effects ; 
 int /*<<< orphan*/  gs_effects ; 
 int /*<<< orphan*/  send_converted_effect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_emux_port*,struct snd_midi_channel*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 

void
snd_emux_nrpn(void *p, struct snd_midi_channel *chan,
	      struct snd_midi_channel_set *chset)
{
	struct snd_emux_port *port;

	port = p;
	if (snd_BUG_ON(!port || !chan))
		return;

	if (chan->control[MIDI_CTL_NONREG_PARM_NUM_MSB] == 127 &&
	    chan->control[MIDI_CTL_NONREG_PARM_NUM_LSB] <= 26) {
		int val;
		/* Win/DOS AWE32 specific NRPNs */
		/* both MSB/LSB necessary */
		val = (chan->control[MIDI_CTL_MSB_DATA_ENTRY] << 7) |
			chan->control[MIDI_CTL_LSB_DATA_ENTRY]; 
		val -= 8192;
		send_converted_effect
			(awe_effects, ARRAY_SIZE(awe_effects),
			 port, chan, chan->control[MIDI_CTL_NONREG_PARM_NUM_LSB],
			 val, EMUX_FX_FLAG_SET);
		return;
	}

	if (port->chset.midi_mode == SNDRV_MIDI_MODE_GS &&
	    chan->control[MIDI_CTL_NONREG_PARM_NUM_MSB] == 1) {
		int val;
		/* GS specific NRPNs */
		/* only MSB is valid */
		val = chan->control[MIDI_CTL_MSB_DATA_ENTRY];
		send_converted_effect
			(gs_effects, ARRAY_SIZE(gs_effects),
			 port, chan, chan->control[MIDI_CTL_NONREG_PARM_NUM_LSB],
			 val, EMUX_FX_FLAG_ADD);
		return;
	}
}