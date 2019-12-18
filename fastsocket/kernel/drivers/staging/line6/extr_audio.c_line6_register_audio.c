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
struct usb_line6 {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int snd_card_register (int /*<<< orphan*/ ) ; 

int line6_register_audio(struct usb_line6 *line6)
{
	int err;

	err = snd_card_register(line6->card);
	if (err < 0)
		return err;

	return 0;
}