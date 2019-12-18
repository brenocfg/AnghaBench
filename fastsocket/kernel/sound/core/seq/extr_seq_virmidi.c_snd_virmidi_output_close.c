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
struct snd_virmidi {int /*<<< orphan*/  parser; } ;
struct snd_rawmidi_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct snd_virmidi* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_virmidi*) ; 
 int /*<<< orphan*/  snd_midi_event_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_virmidi_output_close(struct snd_rawmidi_substream *substream)
{
	struct snd_virmidi *vmidi = substream->runtime->private_data;
	snd_midi_event_free(vmidi->parser);
	substream->runtime->private_data = NULL;
	kfree(vmidi);
	return 0;
}