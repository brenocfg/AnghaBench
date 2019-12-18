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
struct snd_wss {int hardware; TYPE_1__* pcm; struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int WSS_HW_AD1848_MASK ; 
 int WSS_HW_OPTI93X ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/ * snd_ad1848_controls ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_wss*) ; 
 int /*<<< orphan*/ * snd_opti93x_controls ; 
 int /*<<< orphan*/ * snd_wss_controls ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_wss_mixer(struct snd_wss *chip)
{
	struct snd_card *card;
	unsigned int idx;
	int err;

	if (snd_BUG_ON(!chip || !chip->pcm))
		return -EINVAL;

	card = chip->card;

	strcpy(card->mixername, chip->pcm->name);

	if (chip->hardware == WSS_HW_OPTI93X)
		for (idx = 0; idx < ARRAY_SIZE(snd_opti93x_controls); idx++) {
			err = snd_ctl_add(card,
					snd_ctl_new1(&snd_opti93x_controls[idx],
						     chip));
			if (err < 0)
				return err;
		}
	else if (chip->hardware & WSS_HW_AD1848_MASK)
		for (idx = 0; idx < ARRAY_SIZE(snd_ad1848_controls); idx++) {
			err = snd_ctl_add(card,
					snd_ctl_new1(&snd_ad1848_controls[idx],
						     chip));
			if (err < 0)
				return err;
		}
	else
		for (idx = 0; idx < ARRAY_SIZE(snd_wss_controls); idx++) {
			err = snd_ctl_add(card,
					snd_ctl_new1(&snd_wss_controls[idx],
						     chip));
			if (err < 0)
				return err;
		}
	return 0;
}