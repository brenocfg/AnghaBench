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
struct snd_virmidi_dev {int /*<<< orphan*/  filelist_lock; int /*<<< orphan*/  filelist; int /*<<< orphan*/  port; int /*<<< orphan*/  client; int /*<<< orphan*/  seq_mode; } ;
struct snd_virmidi {struct snd_virmidi_dev* rdev; int /*<<< orphan*/  list; int /*<<< orphan*/  port; int /*<<< orphan*/  client; int /*<<< orphan*/  seq_mode; int /*<<< orphan*/  parser; struct snd_rawmidi_substream* substream; } ;
struct snd_rawmidi_substream {struct snd_rawmidi_runtime* runtime; TYPE_1__* rmidi; } ;
struct snd_rawmidi_runtime {struct snd_virmidi* private_data; } ;
struct TYPE_2__ {struct snd_virmidi_dev* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct snd_virmidi*) ; 
 struct snd_virmidi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_midi_event_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_virmidi_input_open(struct snd_rawmidi_substream *substream)
{
	struct snd_virmidi_dev *rdev = substream->rmidi->private_data;
	struct snd_rawmidi_runtime *runtime = substream->runtime;
	struct snd_virmidi *vmidi;
	unsigned long flags;

	vmidi = kzalloc(sizeof(*vmidi), GFP_KERNEL);
	if (vmidi == NULL)
		return -ENOMEM;
	vmidi->substream = substream;
	if (snd_midi_event_new(0, &vmidi->parser) < 0) {
		kfree(vmidi);
		return -ENOMEM;
	}
	vmidi->seq_mode = rdev->seq_mode;
	vmidi->client = rdev->client;
	vmidi->port = rdev->port;	
	runtime->private_data = vmidi;
	write_lock_irqsave(&rdev->filelist_lock, flags);
	list_add_tail(&vmidi->list, &rdev->filelist);
	write_unlock_irqrestore(&rdev->filelist_lock, flags);
	vmidi->rdev = rdev;
	return 0;
}