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
struct snd_device {struct snd_card* device_data; } ;
struct snd_card {int number; } ;

/* Variables and functions */
 int ENXIO ; 
 int SNDRV_CARDS ; 
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_CONTROL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_ctl_f_ops ; 
 int snd_register_device (int /*<<< orphan*/ ,struct snd_card*,int,int /*<<< orphan*/ *,struct snd_card*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int snd_ctl_dev_register(struct snd_device *device)
{
	struct snd_card *card = device->device_data;
	int err, cardnum;
	char name[16];

	if (snd_BUG_ON(!card))
		return -ENXIO;
	cardnum = card->number;
	if (snd_BUG_ON(cardnum < 0 || cardnum >= SNDRV_CARDS))
		return -ENXIO;
	sprintf(name, "controlC%i", cardnum);
	if ((err = snd_register_device(SNDRV_DEVICE_TYPE_CONTROL, card, -1,
				       &snd_ctl_f_ops, card, name)) < 0)
		return err;
	return 0;
}