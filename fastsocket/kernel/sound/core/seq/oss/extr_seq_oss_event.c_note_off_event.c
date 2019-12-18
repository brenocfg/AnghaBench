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
struct snd_seq_event {int dummy; } ;
struct TYPE_3__ {int event_passing; } ;
struct seq_oss_synthinfo {int nr_voices; TYPE_2__* ch; TYPE_1__ arg; } ;
struct seq_oss_devinfo {struct seq_oss_synthinfo* synths; } ;
struct TYPE_4__ {int note; int /*<<< orphan*/  vel; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_NOTEOFF ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_NOTEON ; 
#define  SNDRV_SEQ_OSS_PASS_EVENTS 130 
#define  SNDRV_SEQ_OSS_PROCESS_EVENTS 129 
#define  SNDRV_SEQ_OSS_PROCESS_KEYPRESS 128 
 int set_note_event (struct seq_oss_devinfo*,int,int /*<<< orphan*/ ,int,int,int,struct snd_seq_event*) ; 

__attribute__((used)) static int
note_off_event(struct seq_oss_devinfo *dp, int dev, int ch, int note, int vel, struct snd_seq_event *ev)
{
	struct seq_oss_synthinfo *info = &dp->synths[dev];
	switch (info->arg.event_passing) {
	case SNDRV_SEQ_OSS_PROCESS_EVENTS:
		if (! info->ch || ch < 0 || ch >= info->nr_voices) {
			/* pass directly */
			return set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);
		}

		if (info->ch[ch].note >= 0) {
			note = info->ch[ch].note;
			info->ch[ch].vel = 0;
			info->ch[ch].note = -1;
			return set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEOFF, ch, note, vel, ev);
		}
		return -EINVAL; /* invalid */

	case SNDRV_SEQ_OSS_PASS_EVENTS:
	case SNDRV_SEQ_OSS_PROCESS_KEYPRESS:
		/* pass the event anyway */
		return set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEOFF, ch, note, vel, ev);

	}
	return -EINVAL;
}