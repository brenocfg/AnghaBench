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
struct snd_minor {int type; int card; int device; } ;
struct snd_card {int number; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct snd_minor**) ; 
 struct snd_minor** snd_minors ; 

__attribute__((used)) static int find_snd_minor(int type, struct snd_card *card, int dev)
{
	int cardnum, minor;
	struct snd_minor *mptr;

	cardnum = card ? card->number : -1;
	for (minor = 0; minor < ARRAY_SIZE(snd_minors); ++minor)
		if ((mptr = snd_minors[minor]) != NULL &&
		    mptr->type == type &&
		    mptr->card == cardnum &&
		    mptr->device == dev)
			return minor;
	return -1;
}