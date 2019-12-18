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
struct TYPE_2__ {int /*<<< orphan*/ * sndcard; int /*<<< orphan*/  alt_max_pkt_size; } ;
struct cx231xx {int has_alsa_audio; TYPE_1__ adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx231xx_audio_fini(struct cx231xx *dev)
{
	if (dev == NULL)
		return 0;

	if (dev->has_alsa_audio != 1) {
		/* This device does not support the extension (in this case
		   the device is expecting the snd-usb-audio module or
		   doesn't have analog audio support at all) */
		return 0;
	}

	if (dev->adev.sndcard) {
		snd_card_free(dev->adev.sndcard);
		kfree(dev->adev.alt_max_pkt_size);
		dev->adev.sndcard = NULL;
	}

	return 0;
}