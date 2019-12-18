#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_seq_event {int /*<<< orphan*/  type; } ;
struct snd_midi_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_NONE ; 
 int snd_midi_event_encode_byte (struct snd_midi_event*,int /*<<< orphan*/ ,struct snd_seq_event*) ; 

long snd_midi_event_encode(struct snd_midi_event *dev, unsigned char *buf, long count,
			   struct snd_seq_event *ev)
{
	long result = 0;
	int rc;

	ev->type = SNDRV_SEQ_EVENT_NONE;

	while (count-- > 0) {
		rc = snd_midi_event_encode_byte(dev, *buf++, ev);
		result++;
		if (rc < 0)
			return rc;
		else if (rc > 0)
			return result;
	}

	return result;
}