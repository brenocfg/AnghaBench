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

__attribute__((used)) static int legacy_dvb_usb_getkeycode(struct input_dev *dev,
				int scancode, int *keycode)
{
	struct dvb_usb_device *d = input_get_drvdata(dev);

	struct dvb_usb_rc_key *keymap = d->props.rc_key_map;
	int i;

	/* See if we can match the raw key code. */
	for (i = 0; i < d->props.rc_key_map_size; i++)
		if (keymap[i].scan == scancode) {
			*keycode = keymap[i].event;
			return 0;
		}

	/*
	 * If is there extra space, returns KEY_RESERVED,
	 * otherwise, input core won't let legacy_dvb_usb_setkeycode
	 * to work
	 */
	for (i = 0; i < d->props.rc_key_map_size; i++)
		if (keymap[i].event == KEY_RESERVED ||
		    keymap[i].event == KEY_UNKNOWN) {
			*keycode = KEY_RESERVED;
			return 0;
		}

	return -EINVAL;
}