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
struct saa7134_dev {size_t nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** snd_saa7134_cards ; 

__attribute__((used)) static int alsa_device_exit(struct saa7134_dev *dev)
{

	snd_card_free(snd_saa7134_cards[dev->nr]);
	snd_saa7134_cards[dev->nr] = NULL;
	return 1;
}