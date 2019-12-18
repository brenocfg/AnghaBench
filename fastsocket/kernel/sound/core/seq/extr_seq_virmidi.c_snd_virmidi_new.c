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
struct snd_virmidi_dev {int device; int client; int /*<<< orphan*/  seq_mode; int /*<<< orphan*/  filelist; int /*<<< orphan*/  filelist_lock; struct snd_rawmidi* rmidi; struct snd_card* card; } ;
struct snd_rawmidi {int info_flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  private_free; struct snd_virmidi_dev* private_data; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_VIRMIDI_SEQ_DISPATCH ; 
 struct snd_virmidi_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_device_free (struct snd_card*,struct snd_rawmidi*) ; 
 int snd_rawmidi_new (struct snd_card*,char*,int,int,int,struct snd_rawmidi**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (struct snd_rawmidi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_virmidi_free ; 
 int /*<<< orphan*/  snd_virmidi_global_ops ; 
 int /*<<< orphan*/  snd_virmidi_input_ops ; 
 int /*<<< orphan*/  snd_virmidi_output_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_virmidi_new(struct snd_card *card, int device, struct snd_rawmidi **rrmidi)
{
	struct snd_rawmidi *rmidi;
	struct snd_virmidi_dev *rdev;
	int err;
	
	*rrmidi = NULL;
	if ((err = snd_rawmidi_new(card, "VirMidi", device,
				   16,	/* may be configurable */
				   16,	/* may be configurable */
				   &rmidi)) < 0)
		return err;
	strcpy(rmidi->name, rmidi->id);
	rdev = kzalloc(sizeof(*rdev), GFP_KERNEL);
	if (rdev == NULL) {
		snd_device_free(card, rmidi);
		return -ENOMEM;
	}
	rdev->card = card;
	rdev->rmidi = rmidi;
	rdev->device = device;
	rdev->client = -1;
	rwlock_init(&rdev->filelist_lock);
	INIT_LIST_HEAD(&rdev->filelist);
	rdev->seq_mode = SNDRV_VIRMIDI_SEQ_DISPATCH;
	rmidi->private_data = rdev;
	rmidi->private_free = snd_virmidi_free;
	rmidi->ops = &snd_virmidi_global_ops;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_virmidi_input_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_virmidi_output_ops);
	rmidi->info_flags = SNDRV_RAWMIDI_INFO_INPUT |
			    SNDRV_RAWMIDI_INFO_OUTPUT |
			    SNDRV_RAWMIDI_INFO_DUPLEX;
	*rrmidi = rmidi;
	return 0;
}