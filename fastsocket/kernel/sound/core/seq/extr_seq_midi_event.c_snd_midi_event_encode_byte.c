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
struct TYPE_4__ {int len; int* ptr; } ;
struct TYPE_5__ {TYPE_1__ ext; } ;
struct snd_seq_event {scalar_t__ type; TYPE_2__ data; int /*<<< orphan*/  flags; } ;
struct snd_midi_event {int type; int* buf; int read; scalar_t__ qlen; int bufsize; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {scalar_t__ event; scalar_t__ qlen; int /*<<< orphan*/  (* encode ) (struct snd_midi_event*,struct snd_seq_event*) ;} ;

/* Variables and functions */
 int MIDI_CMD_COMMON_CLOCK ; 
 int MIDI_CMD_COMMON_SYSEX_END ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_LENGTH_FIXED ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_LENGTH_MASK ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_LENGTH_VARIABLE ; 
 scalar_t__ SNDRV_SEQ_EVENT_NONE ; 
 scalar_t__ SNDRV_SEQ_EVENT_SYSEX ; 
 int ST_INVALID ; 
 int ST_SPECIAL ; 
 int ST_SYSEX ; 
 int /*<<< orphan*/  reset_encode (struct snd_midi_event*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_3__* status_event ; 
 int /*<<< orphan*/  stub1 (struct snd_midi_event*,struct snd_seq_event*) ; 

int snd_midi_event_encode_byte(struct snd_midi_event *dev, int c,
			       struct snd_seq_event *ev)
{
	int rc = 0;
	unsigned long flags;

	c &= 0xff;

	if (c >= MIDI_CMD_COMMON_CLOCK) {
		/* real-time event */
		ev->type = status_event[ST_SPECIAL + c - 0xf0].event;
		ev->flags &= ~SNDRV_SEQ_EVENT_LENGTH_MASK;
		ev->flags |= SNDRV_SEQ_EVENT_LENGTH_FIXED;
		return ev->type != SNDRV_SEQ_EVENT_NONE;
	}

	spin_lock_irqsave(&dev->lock, flags);
	if ((c & 0x80) &&
	    (c != MIDI_CMD_COMMON_SYSEX_END || dev->type != ST_SYSEX)) {
		/* new command */
		dev->buf[0] = c;
		if ((c & 0xf0) == 0xf0) /* system messages */
			dev->type = (c & 0x0f) + ST_SPECIAL;
		else
			dev->type = (c >> 4) & 0x07;
		dev->read = 1;
		dev->qlen = status_event[dev->type].qlen;
	} else {
		if (dev->qlen > 0) {
			/* rest of command */
			dev->buf[dev->read++] = c;
			if (dev->type != ST_SYSEX)
				dev->qlen--;
		} else {
			/* running status */
			dev->buf[1] = c;
			dev->qlen = status_event[dev->type].qlen - 1;
			dev->read = 2;
		}
	}
	if (dev->qlen == 0) {
		ev->type = status_event[dev->type].event;
		ev->flags &= ~SNDRV_SEQ_EVENT_LENGTH_MASK;
		ev->flags |= SNDRV_SEQ_EVENT_LENGTH_FIXED;
		if (status_event[dev->type].encode) /* set data values */
			status_event[dev->type].encode(dev, ev);
		if (dev->type >= ST_SPECIAL)
			dev->type = ST_INVALID;
		rc = 1;
	} else 	if (dev->type == ST_SYSEX) {
		if (c == MIDI_CMD_COMMON_SYSEX_END ||
		    dev->read >= dev->bufsize) {
			ev->flags &= ~SNDRV_SEQ_EVENT_LENGTH_MASK;
			ev->flags |= SNDRV_SEQ_EVENT_LENGTH_VARIABLE;
			ev->type = SNDRV_SEQ_EVENT_SYSEX;
			ev->data.ext.len = dev->read;
			ev->data.ext.ptr = dev->buf;
			if (c != MIDI_CMD_COMMON_SYSEX_END)
				dev->read = 0; /* continue to parse */
			else
				reset_encode(dev); /* all parsed */
			rc = 1;
		}
	}

	spin_unlock_irqrestore(&dev->lock, flags);
	return rc;
}