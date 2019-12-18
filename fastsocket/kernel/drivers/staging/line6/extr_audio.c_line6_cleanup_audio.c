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
struct usb_line6 {struct snd_card* card; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_disconnect (struct snd_card*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 

void line6_cleanup_audio(struct usb_line6 *line6)
{
	struct snd_card *card = line6->card;

	if (card == NULL)
		return;

	snd_card_disconnect(card);
	snd_card_free(card);
	line6->card = NULL;
}