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
struct snd_card {struct mts64* private_data; } ;
struct pardevice {int dummy; } ;
struct mts64 {scalar_t__ pardev_claimed; struct pardevice* pardev; } ;

/* Variables and functions */
 int /*<<< orphan*/  parport_release (struct pardevice*) ; 
 int /*<<< orphan*/  parport_unregister_device (struct pardevice*) ; 
 int /*<<< orphan*/  snd_mts64_free (struct mts64*) ; 

__attribute__((used)) static void snd_mts64_card_private_free(struct snd_card *card)
{
	struct mts64 *mts = card->private_data;
	struct pardevice *pardev = mts->pardev;

	if (pardev) {
		if (mts->pardev_claimed)
			parport_release(pardev);
		parport_unregister_device(pardev);
	}

	snd_mts64_free(mts);
}