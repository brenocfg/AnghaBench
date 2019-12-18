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
struct input_dev {int dummy; } ;
struct dvb_usb_rc_key {int scan; int event; } ;
struct TYPE_2__ {int rc_key_map_size; struct dvb_usb_rc_key* rc_key_map; } ;
struct dvb_usb_device {TYPE_1__ props; } ;

/* Variables and functions */
 int EINVAL ; 
 int KEY_RESERVED ; 
 int KEY_UNKNOWN ; 
 struct dvb_usb_device* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int legacy_dvb_usb_setkeycode(struct input_dev *dev,
				int scancode, int keycode)
{
	struct dvb_usb_device *d = input_get_drvdata(dev);

	struct dvb_usb_rc_key *keymap = d->props.rc_key_map;
	int i;

	/* Search if it is replacing an existing keycode */
	for (i = 0; i < d->props.rc_key_map_size; i++)
		if (keymap[i].scan == scancode) {
			keymap[i].event = keycode;
			return 0;
		}

	/* Search if is there a clean entry. If so, use it */
	for (i = 0; i < d->props.rc_key_map_size; i++)
		if (keymap[i].event == KEY_RESERVED ||
		    keymap[i].event == KEY_UNKNOWN) {
			keymap[i].scan = scancode;
			keymap[i].event = keycode;
			return 0;
		}

	/*
	 * FIXME: Currently, it is not possible to increase the size of
	 * scancode table. For it to happen, one possibility
	 * would be to allocate a table with key_map_size + 1,
	 * copying data, appending the new key on it, and freeing
	 * the old one - or maybe just allocating some spare space
	 */

	return -EINVAL;
}