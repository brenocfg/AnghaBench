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
struct TYPE_2__ {int cmd; int p1; int /*<<< orphan*/  dev; int /*<<< orphan*/  chn; scalar_t__ p2; scalar_t__ p3; } ;
union evrec {int /*<<< orphan*/  c; TYPE_1__ e; } ;
struct snd_seq_event {int dummy; } ;
struct seq_oss_devinfo {int dummy; } ;

/* Variables and functions */
 int CTL_PAN ; 
#define  CTRL_PITCH_BENDER 136 
#define  CTRL_PITCH_BENDER_RANGE 135 
 int EINVAL ; 
#define  SEQ_AFTERTOUCH 134 
#define  SEQ_BALANCE 133 
#define  SEQ_CONTROLLER 132 
#define  SEQ_NOTEOFF 131 
#define  SEQ_NOTEON 130 
#define  SEQ_PGMCHANGE 129 
#define  SEQ_VOLMODE 128 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_CHANPRESS ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_CONTROL14 ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_CONTROLLER ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_PGMCHANGE ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_PITCHBEND ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_REGPARAM ; 
 int note_off_event (struct seq_oss_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,struct snd_seq_event*) ; 
 int note_on_event (struct seq_oss_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,struct snd_seq_event*) ; 
 int set_control_event (struct seq_oss_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct snd_seq_event*) ; 
 int snd_seq_oss_synth_raw_event (struct seq_oss_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_event*) ; 

__attribute__((used)) static int
extended_event(struct seq_oss_devinfo *dp, union evrec *q, struct snd_seq_event *ev)
{
	int val;

	switch (q->e.cmd) {
	case SEQ_NOTEOFF:
		return note_off_event(dp, q->e.dev, q->e.chn, q->e.p1, q->e.p2, ev);

	case SEQ_NOTEON:
		return note_on_event(dp, q->e.dev, q->e.chn, q->e.p1, q->e.p2, ev);

	case SEQ_PGMCHANGE:
		return set_control_event(dp, q->e.dev, SNDRV_SEQ_EVENT_PGMCHANGE,
					 q->e.chn, 0, q->e.p1, ev);

	case SEQ_AFTERTOUCH:
		return set_control_event(dp, q->e.dev, SNDRV_SEQ_EVENT_CHANPRESS,
					 q->e.chn, 0, q->e.p1, ev);

	case SEQ_BALANCE:
		/* convert -128:127 to 0:127 */
		val = (char)q->e.p1;
		val = (val + 128) / 2;
		return set_control_event(dp, q->e.dev, SNDRV_SEQ_EVENT_CONTROLLER,
					 q->e.chn, CTL_PAN, val, ev);

	case SEQ_CONTROLLER:
		val = ((short)q->e.p3 << 8) | (short)q->e.p2;
		switch (q->e.p1) {
		case CTRL_PITCH_BENDER: /* SEQ1 V2 control */
			/* -0x2000:0x1fff */
			return set_control_event(dp, q->e.dev,
						 SNDRV_SEQ_EVENT_PITCHBEND,
						 q->e.chn, 0, val, ev);
		case CTRL_PITCH_BENDER_RANGE:
			/* conversion: 100/semitone -> 128/semitone */
			return set_control_event(dp, q->e.dev,
						 SNDRV_SEQ_EVENT_REGPARAM,
						 q->e.chn, 0, val*128/100, ev);
		default:
			return set_control_event(dp, q->e.dev,
						  SNDRV_SEQ_EVENT_CONTROL14,
						  q->e.chn, q->e.p1, val, ev);
		}

	case SEQ_VOLMODE:
		return snd_seq_oss_synth_raw_event(dp, q->e.dev, q->c, ev);

	}
	return -EINVAL;
}