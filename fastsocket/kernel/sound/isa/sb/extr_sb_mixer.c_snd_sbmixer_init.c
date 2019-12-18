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
struct snd_sb {int /*<<< orphan*/  mixer_lock; struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  mixername; } ;
struct sbmix_elem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_component_add (struct snd_card*,char*) ; 
 int snd_sbmixer_add_ctl_elem (struct snd_sb*,struct sbmix_elem*) ; 
 int /*<<< orphan*/  snd_sbmixer_write (struct snd_sb*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_sbmixer_init(struct snd_sb *chip,
			    struct sbmix_elem **controls,
			    int controls_count,
			    unsigned char map[][2],
			    int map_count,
			    char *name)
{
	unsigned long flags;
	struct snd_card *card = chip->card;
	int idx, err;

	/* mixer reset */
	spin_lock_irqsave(&chip->mixer_lock, flags);
	snd_sbmixer_write(chip, 0x00, 0x00);
	spin_unlock_irqrestore(&chip->mixer_lock, flags);

	/* mute and zero volume channels */
	for (idx = 0; idx < map_count; idx++) {
		spin_lock_irqsave(&chip->mixer_lock, flags);
		snd_sbmixer_write(chip, map[idx][0], map[idx][1]);
		spin_unlock_irqrestore(&chip->mixer_lock, flags);
	}

	for (idx = 0; idx < controls_count; idx++) {
		if ((err = snd_sbmixer_add_ctl_elem(chip, controls[idx])) < 0)
			return err;
	}
	snd_component_add(card, name);
	strcpy(card->mixername, name);
	return 0;
}