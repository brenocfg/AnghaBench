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
struct snd_card {int /*<<< orphan*/  files_lock; scalar_t__ shutdown; } ;
struct hda_bus {struct snd_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void snd_hda_unlock_devices(struct hda_bus *bus)
{
	struct snd_card *card = bus->card;

	card = bus->card;
	spin_lock(&card->files_lock);
	card->shutdown = 0;
	spin_unlock(&card->files_lock);
}