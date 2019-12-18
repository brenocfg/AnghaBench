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
struct TYPE_4__ {int channel; int note; int velocity; } ;
struct TYPE_3__ {TYPE_2__ note; } ;
struct snd_seq_event {int type; TYPE_1__ data; } ;
struct seq_oss_devinfo {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  snd_seq_oss_synth_addr (struct seq_oss_devinfo*,int,struct snd_seq_event*) ; 
 int /*<<< orphan*/  snd_seq_oss_synth_is_valid (struct seq_oss_devinfo*,int) ; 

__attribute__((used)) static int
set_note_event(struct seq_oss_devinfo *dp, int dev, int type, int ch, int note, int vel, struct snd_seq_event *ev)
{
	if (! snd_seq_oss_synth_is_valid(dp, dev))
		return -ENXIO;
	
	ev->type = type;
	snd_seq_oss_synth_addr(dp, dev, ev);
	ev->data.note.channel = ch;
	ev->data.note.note = note;
	ev->data.note.velocity = vel;

	return 0;
}