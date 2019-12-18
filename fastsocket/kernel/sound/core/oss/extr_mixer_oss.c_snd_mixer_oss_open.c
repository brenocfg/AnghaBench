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
struct snd_mixer_oss_file {int /*<<< orphan*/ * mixer; struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  module; } ;
struct inode {int dummy; } ;
struct file {struct snd_mixer_oss_file* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mixer_oss; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_OSS_DEVICE_TYPE_MIXER ; 
 TYPE_1__* card_oss (struct snd_card*) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct snd_mixer_oss_file*) ; 
 struct snd_mixer_oss_file* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int snd_card_file_add (struct snd_card*,struct file*) ; 
 int /*<<< orphan*/  snd_card_file_remove (struct snd_card*,struct file*) ; 
 struct snd_card* snd_lookup_oss_minor_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_mixer_oss_open(struct inode *inode, struct file *file)
{
	struct snd_card *card;
	struct snd_mixer_oss_file *fmixer;
	int err;

	err = nonseekable_open(inode, file);
	if (err < 0)
		return err;

	card = snd_lookup_oss_minor_data(iminor(inode),
					 SNDRV_OSS_DEVICE_TYPE_MIXER);
	if (card == NULL)
		return -ENODEV;
	if (card_oss(card)->mixer_oss == NULL)
		return -ENODEV;
	err = snd_card_file_add(card, file);
	if (err < 0)
		return err;
	fmixer = kzalloc(sizeof(*fmixer), GFP_KERNEL);
	if (fmixer == NULL) {
		snd_card_file_remove(card, file);
		return -ENOMEM;
	}
	fmixer->card = card;
	fmixer->mixer = card_oss(card)->mixer_oss;
	file->private_data = fmixer;
	if (!try_module_get(card->module)) {
		kfree(fmixer);
		snd_card_file_remove(card, file);
		return -EFAULT;
	}
	return 0;
}