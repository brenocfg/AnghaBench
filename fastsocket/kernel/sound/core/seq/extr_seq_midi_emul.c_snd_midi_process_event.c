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
typedef  int /*<<< orphan*/  sysexbuf ;
struct TYPE_6__ {int param; int value; } ;
struct TYPE_4__ {int channel; scalar_t__ velocity; int note; } ;
struct TYPE_5__ {TYPE_3__ control; TYPE_1__ note; } ;
struct snd_seq_event {int type; int flags; TYPE_2__ data; } ;
struct snd_midi_op {int /*<<< orphan*/  (* control ) (void*,int /*<<< orphan*/ ,struct snd_midi_channel*) ;int /*<<< orphan*/  (* key_press ) (void*,size_t,scalar_t__,struct snd_midi_channel*) ;int /*<<< orphan*/  (* note_off ) (void*,size_t,int /*<<< orphan*/ ,struct snd_midi_channel*) ;int /*<<< orphan*/  (* note_on ) (void*,size_t,scalar_t__,struct snd_midi_channel*) ;} ;
struct snd_midi_channel_set {int max_channels; void* private_data; struct snd_midi_channel* channels; } ;
struct snd_midi_channel {int* note; int midi_program; int midi_pitchbend; int midi_pressure; int* control; int /*<<< orphan*/  param_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIDI_CTL_CHAN_PRESSURE ; 
 size_t MIDI_CTL_LSB_DATA_ENTRY ; 
 size_t MIDI_CTL_MSB_DATA_ENTRY ; 
 size_t MIDI_CTL_NONREG_PARM_NUM_LSB ; 
 size_t MIDI_CTL_NONREG_PARM_NUM_MSB ; 
 int /*<<< orphan*/  MIDI_CTL_PITCHBEND ; 
 size_t MIDI_CTL_REGIST_PARM_NUM_LSB ; 
 size_t MIDI_CTL_REGIST_PARM_NUM_MSB ; 
 int SNDRV_MIDI_NOTE_ON ; 
 int /*<<< orphan*/  SNDRV_MIDI_PARAM_TYPE_NONREGISTERED ; 
 int /*<<< orphan*/  SNDRV_MIDI_PARAM_TYPE_REGISTERED ; 
#define  SNDRV_SEQ_EVENT_CHANPRESS 156 
#define  SNDRV_SEQ_EVENT_CLIENT_CHANGE 155 
#define  SNDRV_SEQ_EVENT_CLIENT_EXIT 154 
#define  SNDRV_SEQ_EVENT_CLIENT_START 153 
#define  SNDRV_SEQ_EVENT_CLOCK 152 
#define  SNDRV_SEQ_EVENT_CONTINUE 151 
#define  SNDRV_SEQ_EVENT_CONTROL14 150 
#define  SNDRV_SEQ_EVENT_CONTROLLER 149 
#define  SNDRV_SEQ_EVENT_ECHO 148 
#define  SNDRV_SEQ_EVENT_KEYPRESS 147 
#define  SNDRV_SEQ_EVENT_KEYSIGN 146 
 int SNDRV_SEQ_EVENT_LENGTH_MASK ; 
 int SNDRV_SEQ_EVENT_LENGTH_VARIABLE ; 
#define  SNDRV_SEQ_EVENT_NONREGPARAM 145 
 int SNDRV_SEQ_EVENT_NOTE ; 
#define  SNDRV_SEQ_EVENT_NOTEOFF 144 
#define  SNDRV_SEQ_EVENT_NOTEON 143 
#define  SNDRV_SEQ_EVENT_PGMCHANGE 142 
#define  SNDRV_SEQ_EVENT_PITCHBEND 141 
#define  SNDRV_SEQ_EVENT_PORT_CHANGE 140 
#define  SNDRV_SEQ_EVENT_PORT_EXIT 139 
#define  SNDRV_SEQ_EVENT_PORT_START 138 
#define  SNDRV_SEQ_EVENT_QFRAME 137 
#define  SNDRV_SEQ_EVENT_REGPARAM 136 
#define  SNDRV_SEQ_EVENT_SENSING 135 
#define  SNDRV_SEQ_EVENT_SONGPOS 134 
#define  SNDRV_SEQ_EVENT_SONGSEL 133 
#define  SNDRV_SEQ_EVENT_START 132 
#define  SNDRV_SEQ_EVENT_STOP 131 
#define  SNDRV_SEQ_EVENT_SYSEX 130 
#define  SNDRV_SEQ_EVENT_TEMPO 129 
#define  SNDRV_SEQ_EVENT_TIMESIGN 128 
 int /*<<< orphan*/  do_control (struct snd_midi_op*,void*,struct snd_midi_channel_set*,struct snd_midi_channel*,int,int) ; 
 int /*<<< orphan*/  note_off (struct snd_midi_op*,void*,struct snd_midi_channel*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  nrpn (struct snd_midi_op*,void*,struct snd_midi_channel*,struct snd_midi_channel_set*) ; 
 int /*<<< orphan*/  rpn (struct snd_midi_op*,void*,struct snd_midi_channel*,struct snd_midi_channel_set*) ; 
 int /*<<< orphan*/  snd_printd (char*,...) ; 
 scalar_t__ snd_seq_ev_is_channel_type (struct snd_seq_event*) ; 
 int snd_seq_expand_var_event (struct snd_seq_event*,int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,size_t,int /*<<< orphan*/ ,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  stub2 (void*,size_t,scalar_t__,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  stub3 (void*,size_t,scalar_t__,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  stub4 (void*,int /*<<< orphan*/ ,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  stub5 (void*,int /*<<< orphan*/ ,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  sysex (struct snd_midi_op*,void*,unsigned char*,int,struct snd_midi_channel_set*) ; 

void
snd_midi_process_event(struct snd_midi_op *ops,
		       struct snd_seq_event *ev,
		       struct snd_midi_channel_set *chanset)
{
	struct snd_midi_channel *chan;
	void *drv;
	int dest_channel = 0;

	if (ev == NULL || chanset == NULL) {
		snd_printd("ev or chanbase NULL (snd_midi_process_event)\n");
		return;
	}
	if (chanset->channels == NULL)
		return;

	if (snd_seq_ev_is_channel_type(ev)) {
		dest_channel = ev->data.note.channel;
		if (dest_channel >= chanset->max_channels) {
			snd_printd("dest channel is %d, max is %d\n",
				   dest_channel, chanset->max_channels);
			return;
		}
	}

	chan = chanset->channels + dest_channel;
	drv  = chanset->private_data;

	/* EVENT_NOTE should be processed before queued */
	if (ev->type == SNDRV_SEQ_EVENT_NOTE)
		return;

	/* Make sure that we don't have a note on that should really be
	 * a note off */
	if (ev->type == SNDRV_SEQ_EVENT_NOTEON && ev->data.note.velocity == 0)
		ev->type = SNDRV_SEQ_EVENT_NOTEOFF;

	/* Make sure the note is within array range */
	if (ev->type == SNDRV_SEQ_EVENT_NOTEON ||
	    ev->type == SNDRV_SEQ_EVENT_NOTEOFF ||
	    ev->type == SNDRV_SEQ_EVENT_KEYPRESS) {
		if (ev->data.note.note >= 128)
			return;
	}

	switch (ev->type) {
	case SNDRV_SEQ_EVENT_NOTEON:
		if (chan->note[ev->data.note.note] & SNDRV_MIDI_NOTE_ON) {
			if (ops->note_off)
				ops->note_off(drv, ev->data.note.note, 0, chan);
		}
		chan->note[ev->data.note.note] = SNDRV_MIDI_NOTE_ON;
		if (ops->note_on)
			ops->note_on(drv, ev->data.note.note, ev->data.note.velocity, chan);
		break;
	case SNDRV_SEQ_EVENT_NOTEOFF:
		if (! (chan->note[ev->data.note.note] & SNDRV_MIDI_NOTE_ON))
			break;
		if (ops->note_off)
			note_off(ops, drv, chan, ev->data.note.note, ev->data.note.velocity);
		break;
	case SNDRV_SEQ_EVENT_KEYPRESS:
		if (ops->key_press)
			ops->key_press(drv, ev->data.note.note, ev->data.note.velocity, chan);
		break;
	case SNDRV_SEQ_EVENT_CONTROLLER:
		do_control(ops, drv, chanset, chan,
			   ev->data.control.param, ev->data.control.value);
		break;
	case SNDRV_SEQ_EVENT_PGMCHANGE:
		chan->midi_program = ev->data.control.value;
		break;
	case SNDRV_SEQ_EVENT_PITCHBEND:
		chan->midi_pitchbend = ev->data.control.value;
		if (ops->control)
			ops->control(drv, MIDI_CTL_PITCHBEND, chan);
		break;
	case SNDRV_SEQ_EVENT_CHANPRESS:
		chan->midi_pressure = ev->data.control.value;
		if (ops->control)
			ops->control(drv, MIDI_CTL_CHAN_PRESSURE, chan);
		break;
	case SNDRV_SEQ_EVENT_CONTROL14:
		/* Best guess is that this is any of the 14 bit controller values */
		if (ev->data.control.param < 32) {
			/* set low part first */
			chan->control[ev->data.control.param + 32] =
				ev->data.control.value & 0x7f;
			do_control(ops, drv, chanset, chan,
				   ev->data.control.param,
				   ((ev->data.control.value>>7) & 0x7f));
		} else
			do_control(ops, drv, chanset, chan,
				   ev->data.control.param,
				   ev->data.control.value);
		break;
	case SNDRV_SEQ_EVENT_NONREGPARAM:
		/* Break it back into its controller values */
		chan->param_type = SNDRV_MIDI_PARAM_TYPE_NONREGISTERED;
		chan->control[MIDI_CTL_MSB_DATA_ENTRY]
			= (ev->data.control.value >> 7) & 0x7f;
		chan->control[MIDI_CTL_LSB_DATA_ENTRY]
			= ev->data.control.value & 0x7f;
		chan->control[MIDI_CTL_NONREG_PARM_NUM_MSB]
			= (ev->data.control.param >> 7) & 0x7f;
		chan->control[MIDI_CTL_NONREG_PARM_NUM_LSB]
			= ev->data.control.param & 0x7f;
		nrpn(ops, drv, chan, chanset);
		break;
	case SNDRV_SEQ_EVENT_REGPARAM:
		/* Break it back into its controller values */
		chan->param_type = SNDRV_MIDI_PARAM_TYPE_REGISTERED;
		chan->control[MIDI_CTL_MSB_DATA_ENTRY]
			= (ev->data.control.value >> 7) & 0x7f;
		chan->control[MIDI_CTL_LSB_DATA_ENTRY]
			= ev->data.control.value & 0x7f;
		chan->control[MIDI_CTL_REGIST_PARM_NUM_MSB]
			= (ev->data.control.param >> 7) & 0x7f;
		chan->control[MIDI_CTL_REGIST_PARM_NUM_LSB]
			= ev->data.control.param & 0x7f;
		rpn(ops, drv, chan, chanset);
		break;
	case SNDRV_SEQ_EVENT_SYSEX:
		if ((ev->flags & SNDRV_SEQ_EVENT_LENGTH_MASK) == SNDRV_SEQ_EVENT_LENGTH_VARIABLE) {
			unsigned char sysexbuf[64];
			int len;
			len = snd_seq_expand_var_event(ev, sizeof(sysexbuf), sysexbuf, 1, 0);
			if (len > 0)
				sysex(ops, drv, sysexbuf, len, chanset);
		}
		break;
	case SNDRV_SEQ_EVENT_SONGPOS:
	case SNDRV_SEQ_EVENT_SONGSEL:
	case SNDRV_SEQ_EVENT_CLOCK:
	case SNDRV_SEQ_EVENT_START:
	case SNDRV_SEQ_EVENT_CONTINUE:
	case SNDRV_SEQ_EVENT_STOP:
	case SNDRV_SEQ_EVENT_QFRAME:
	case SNDRV_SEQ_EVENT_TEMPO:
	case SNDRV_SEQ_EVENT_TIMESIGN:
	case SNDRV_SEQ_EVENT_KEYSIGN:
		goto not_yet;
	case SNDRV_SEQ_EVENT_SENSING:
		break;
	case SNDRV_SEQ_EVENT_CLIENT_START:
	case SNDRV_SEQ_EVENT_CLIENT_EXIT:
	case SNDRV_SEQ_EVENT_CLIENT_CHANGE:
	case SNDRV_SEQ_EVENT_PORT_START:
	case SNDRV_SEQ_EVENT_PORT_EXIT:
	case SNDRV_SEQ_EVENT_PORT_CHANGE:
	case SNDRV_SEQ_EVENT_ECHO:
	not_yet:
	default:
		/*snd_printd("Unimplemented event %d\n", ev->type);*/
		break;
	}
}