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
struct snd_card {int /*<<< orphan*/  files_list; int /*<<< orphan*/  shutdown_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int snd_card_disconnect (struct snd_card*) ; 
 int /*<<< orphan*/  snd_card_do_free (struct snd_card*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_card_free(struct snd_card *card)
{
	int ret = snd_card_disconnect(card);
	if (ret)
		return ret;

	/* wait, until all devices are ready for the free operation */
	wait_event(card->shutdown_sleep, list_empty(&card->files_list));
	snd_card_do_free(card);
	return 0;
}