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
struct snd_virmidi_dev {int /*<<< orphan*/  port; int /*<<< orphan*/  client; int /*<<< orphan*/  seq_mode; } ;
struct snd_rawmidi {int /*<<< orphan*/  name; struct snd_virmidi_dev* private_data; } ;
struct snd_emux {int midi_ports; char* name; struct snd_rawmidi** vmidi; int /*<<< orphan*/ * ports; int /*<<< orphan*/  client; scalar_t__ midi_devidx; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_VIRMIDI_SEQ_ATTACH ; 
 struct snd_rawmidi** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_device_free (struct snd_card*,struct snd_rawmidi*) ; 
 scalar_t__ snd_device_register (struct snd_card*,struct snd_rawmidi*) ; 
 int /*<<< orphan*/  snd_emux_delete_virmidi (struct snd_emux*) ; 
 scalar_t__ snd_virmidi_new (struct snd_card*,scalar_t__,struct snd_rawmidi**) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

int snd_emux_init_virmidi(struct snd_emux *emu, struct snd_card *card)
{
	int i;

	emu->vmidi = NULL;
	if (emu->midi_ports <= 0)
		return 0;

	emu->vmidi = kcalloc(emu->midi_ports, sizeof(struct snd_rawmidi *), GFP_KERNEL);
	if (emu->vmidi == NULL)
		return -ENOMEM;

	for (i = 0; i < emu->midi_ports; i++) {
		struct snd_rawmidi *rmidi;
		struct snd_virmidi_dev *rdev;
		if (snd_virmidi_new(card, emu->midi_devidx + i, &rmidi) < 0)
			goto __error;
		rdev = rmidi->private_data;
		sprintf(rmidi->name, "%s Synth MIDI", emu->name);
		rdev->seq_mode = SNDRV_VIRMIDI_SEQ_ATTACH;
		rdev->client = emu->client;
		rdev->port = emu->ports[i];
		if (snd_device_register(card, rmidi) < 0) {
			snd_device_free(card, rmidi);
			goto __error;
		}
		emu->vmidi[i] = rmidi;
		/* snd_printk(KERN_DEBUG "virmidi %d ok\n", i); */
	}
	return 0;

__error:
	/* snd_printk(KERN_DEBUG "error init..\n"); */
	snd_emux_delete_virmidi(emu);
	return -ENOMEM;
}