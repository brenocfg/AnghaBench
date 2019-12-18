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
struct snd_card {int free_on_last_close; int /*<<< orphan*/  files_lock; int /*<<< orphan*/  files_list; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int snd_card_disconnect (struct snd_card*) ; 
 int /*<<< orphan*/  snd_card_do_free (struct snd_card*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int snd_card_free_when_closed(struct snd_card *card)
{
	int free_now = 0;
	int ret = snd_card_disconnect(card);
	if (ret)
		return ret;

	spin_lock(&card->files_lock);
	if (list_empty(&card->files_list))
		free_now = 1;
	else
		card->free_on_last_close = 1;
	spin_unlock(&card->files_lock);

	if (free_now)
		snd_card_do_free(card);
	return 0;
}