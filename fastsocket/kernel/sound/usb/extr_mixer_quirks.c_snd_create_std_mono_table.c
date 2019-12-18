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
struct usb_mixer_interface {int dummy; } ;
struct std_mono_table {int /*<<< orphan*/  tlv_callback; int /*<<< orphan*/ * name; int /*<<< orphan*/  val_type; int /*<<< orphan*/  cmask; int /*<<< orphan*/  control; int /*<<< orphan*/  unitid; } ;

/* Variables and functions */
 int snd_create_std_mono_ctl (struct usb_mixer_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_create_std_mono_table(struct usb_mixer_interface *mixer,
				struct std_mono_table *t)
{
	int err;

	while (t->name != NULL) {
		err = snd_create_std_mono_ctl(mixer, t->unitid, t->control,
				t->cmask, t->val_type, t->name, t->tlv_callback);
		if (err < 0)
			return err;
		t++;
	}

	return 0;
}