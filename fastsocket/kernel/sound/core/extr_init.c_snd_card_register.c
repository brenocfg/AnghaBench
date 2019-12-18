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
struct snd_card {size_t number; char* id; int /*<<< orphan*/ * card_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_MIXER_OSS_NOTIFY_REGISTER ; 
 int /*<<< orphan*/  card_id_attrs ; 
 int /*<<< orphan*/  card_number_attrs ; 
 int /*<<< orphan*/ * device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_card*,char*,size_t) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_info_for_card (struct snd_card*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_card_mutex ; 
 int /*<<< orphan*/  snd_card_set_id_no_lock (struct snd_card*,char*) ; 
 struct snd_card** snd_cards ; 
 int snd_device_register_all (struct snd_card*) ; 
 int /*<<< orphan*/  snd_mixer_oss_notify_callback (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sound_class ; 

int snd_card_register(struct snd_card *card)
{
	int err;

	if (snd_BUG_ON(!card))
		return -EINVAL;
#ifndef CONFIG_SYSFS_DEPRECATED
	if (!card->card_dev) {
		card->card_dev = device_create(sound_class, card->dev,
					       MKDEV(0, 0), card,
					       "card%i", card->number);
		if (IS_ERR(card->card_dev))
			card->card_dev = NULL;
	}
#endif
	if ((err = snd_device_register_all(card)) < 0)
		return err;
	mutex_lock(&snd_card_mutex);
	if (snd_cards[card->number]) {
		/* already registered */
		mutex_unlock(&snd_card_mutex);
		return 0;
	}
	snd_card_set_id_no_lock(card, card->id[0] == '\0' ? NULL : card->id);
	snd_cards[card->number] = card;
	mutex_unlock(&snd_card_mutex);
	init_info_for_card(card);
#if defined(CONFIG_SND_MIXER_OSS) || defined(CONFIG_SND_MIXER_OSS_MODULE)
	if (snd_mixer_oss_notify_callback)
		snd_mixer_oss_notify_callback(card, SND_MIXER_OSS_NOTIFY_REGISTER);
#endif
#ifndef CONFIG_SYSFS_DEPRECATED
	if (card->card_dev) {
		err = device_create_file(card->card_dev, &card_id_attrs);
		if (err < 0)
			return err;
		err = device_create_file(card->card_dev, &card_number_attrs);
		if (err < 0)
			return err;
	}
#endif
	return 0;
}