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
struct snd_card {int dummy; } ;
typedef  int /*<<< orphan*/  fmixer ;
struct TYPE_2__ {int /*<<< orphan*/ * mixer_oss; } ;

/* Variables and functions */
 int ENXIO ; 
 TYPE_1__* card_oss (struct snd_card*) ; 
 int /*<<< orphan*/  memset (struct snd_mixer_oss_file*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_mixer_oss_ioctl1 (struct snd_mixer_oss_file*,unsigned int,unsigned long) ; 

int snd_mixer_oss_ioctl_card(struct snd_card *card, unsigned int cmd, unsigned long arg)
{
	struct snd_mixer_oss_file fmixer;
	
	if (snd_BUG_ON(!card))
		return -ENXIO;
	if (card_oss(card)->mixer_oss == NULL)
		return -ENXIO;
	memset(&fmixer, 0, sizeof(fmixer));
	fmixer.card = card;
	fmixer.mixer = card_oss(card)->mixer_oss;
	return snd_mixer_oss_ioctl1(&fmixer, cmd, arg);
}