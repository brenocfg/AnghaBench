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
struct TYPE_6__ {int /*<<< orphan*/  time; } ;
struct TYPE_5__ {scalar_t__ code; } ;
union evrec {TYPE_3__ t; TYPE_2__ s; } ;
struct TYPE_4__ {scalar_t__ client; } ;
struct snd_seq_event {scalar_t__ type; int /*<<< orphan*/  data; TYPE_1__ source; } ;
struct seq_oss_devinfo {scalar_t__ cseq; int /*<<< orphan*/ * readq; int /*<<< orphan*/  writeq; } ;

/* Variables and functions */
 scalar_t__ SEQ_SYNCTIMER ; 
 scalar_t__ SNDRV_SEQ_EVENT_ECHO ; 
 int snd_seq_oss_midi_input (struct snd_seq_event*,int,void*) ; 
 int /*<<< orphan*/  snd_seq_oss_readq_put_event (int /*<<< orphan*/ *,union evrec*) ; 
 int /*<<< orphan*/  snd_seq_oss_writeq_wakeup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
snd_seq_oss_event_input(struct snd_seq_event *ev, int direct, void *private_data,
			int atomic, int hop)
{
	struct seq_oss_devinfo *dp = (struct seq_oss_devinfo *)private_data;
	union evrec *rec;

	if (ev->type != SNDRV_SEQ_EVENT_ECHO)
		return snd_seq_oss_midi_input(ev, direct, private_data);

	if (ev->source.client != dp->cseq)
		return 0; /* ignored */

	rec = (union evrec*)&ev->data;
	if (rec->s.code == SEQ_SYNCTIMER) {
		/* sync echo back */
		snd_seq_oss_writeq_wakeup(dp->writeq, rec->t.time);
		
	} else {
		/* echo back event */
		if (dp->readq == NULL)
			return 0;
		snd_seq_oss_readq_put_event(dp->readq, rec);
	}
	return 0;
}