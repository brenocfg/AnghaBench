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
struct TYPE_2__ {int chn; int cmd; int /*<<< orphan*/  val; int /*<<< orphan*/  dev; int /*<<< orphan*/  p1; } ;
union evrec {TYPE_1__ l; } ;
struct snd_seq_event {int dummy; } ;
struct seq_oss_devinfo {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MIDI_CHN_PRESSURE 131 
#define  MIDI_CTL_CHANGE 130 
#define  MIDI_PGM_CHANGE 129 
#define  MIDI_PITCH_BEND 128 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_CHANPRESS ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_CONTROLLER ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_PGMCHANGE ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_PITCHBEND ; 
 int set_control_event (struct seq_oss_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_event*) ; 

__attribute__((used)) static int
chn_common_event(struct seq_oss_devinfo *dp, union evrec *q, struct snd_seq_event *ev)
{
	if (q->l.chn >= 32)
		return -EINVAL;
	switch (q->l.cmd) {
	case MIDI_PGM_CHANGE:
		return set_control_event(dp, q->l.dev, SNDRV_SEQ_EVENT_PGMCHANGE,
					  q->l.chn, 0, q->l.p1, ev);

	case MIDI_CTL_CHANGE:
		return set_control_event(dp, q->l.dev, SNDRV_SEQ_EVENT_CONTROLLER,
					  q->l.chn, q->l.p1, q->l.val, ev);

	case MIDI_PITCH_BEND:
		/* conversion: 0:0x3fff -> -0x2000:0x1fff */
		return set_control_event(dp, q->l.dev, SNDRV_SEQ_EVENT_PITCHBEND,
					  q->l.chn, 0, q->l.val - 8192, ev);
		
	case MIDI_CHN_PRESSURE:
		return set_control_event(dp, q->l.dev, SNDRV_SEQ_EVENT_CHANPRESS,
					  q->l.chn, 0, q->l.val, ev);
	}
	return -EINVAL;
}