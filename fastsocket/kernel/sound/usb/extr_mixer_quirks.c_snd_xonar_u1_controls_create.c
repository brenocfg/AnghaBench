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
struct usb_mixer_interface {int xonar_u1_status; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct usb_mixer_interface*) ; 
 int /*<<< orphan*/  snd_xonar_u1_output_switch ; 

__attribute__((used)) static int snd_xonar_u1_controls_create(struct usb_mixer_interface *mixer)
{
	int err;

	err = snd_ctl_add(mixer->chip->card,
			  snd_ctl_new1(&snd_xonar_u1_output_switch, mixer));
	if (err < 0)
		return err;
	mixer->xonar_u1_status = 0x05;
	return 0;
}