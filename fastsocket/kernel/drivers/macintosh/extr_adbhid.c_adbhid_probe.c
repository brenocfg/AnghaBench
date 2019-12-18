#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct adb_request {int reply_len; int* reply; } ;
struct TYPE_5__ {int nids; int* id; } ;

/* Variables and functions */
 int ADBMOUSE_EXTENDED ; 
 int ADBMOUSE_MACALLY2 ; 
 int ADBMOUSE_MICROSPEED ; 
 int ADBMOUSE_MS_A3 ; 
 int ADBMOUSE_STANDARD_100 ; 
 int ADBMOUSE_STANDARD_200 ; 
 int ADBMOUSE_TRACKBALL ; 
 int ADBMOUSE_TRACKBALLPRO ; 
 int ADBMOUSE_TRACKPAD ; 
 int ADBMOUSE_TURBOMOUSE5 ; 
 int ADBREQ_REPLY ; 
 int ADBREQ_SYNC ; 
 int /*<<< orphan*/  ADB_KEYBOARD ; 
 int /*<<< orphan*/  ADB_MISC ; 
 int /*<<< orphan*/  ADB_MOUSE ; 
 int /*<<< orphan*/  ADB_READREG (int,int) ; 
 int /*<<< orphan*/  ADB_WRITEREG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYB_LEDREG ; 
 int /*<<< orphan*/  adb_get_infos (int,int*,int*) ; 
 int /*<<< orphan*/  adb_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adb_request (struct adb_request*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ adb_try_handler_change (int,int) ; 
 int /*<<< orphan*/  adbhid_buttons_input ; 
 int /*<<< orphan*/  adbhid_input_devcleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adbhid_input_reregister (int,int,int,int,int) ; 
 int /*<<< orphan*/  adbhid_keyboard_input ; 
 int /*<<< orphan*/  adbhid_mouse_input ; 
 TYPE_1__ buttons_ids ; 
 int /*<<< orphan*/  init_microspeed (int) ; 
 int /*<<< orphan*/  init_ms_a3 (int) ; 
 int /*<<< orphan*/  init_trackball (int) ; 
 int /*<<< orphan*/  init_trackpad (int) ; 
 int /*<<< orphan*/  init_turbomouse (int) ; 
 TYPE_1__ keyboard_ids ; 
 TYPE_1__ mouse_ids ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
adbhid_probe(void)
{
	struct adb_request req;
	int i, default_id, org_handler_id, cur_handler_id;
	u16 reg = 0;

	adb_register(ADB_MOUSE, 0, &mouse_ids, adbhid_mouse_input);
	adb_register(ADB_KEYBOARD, 0, &keyboard_ids, adbhid_keyboard_input);
	adb_register(ADB_MISC, 0, &buttons_ids, adbhid_buttons_input);

	for (i = 0; i < keyboard_ids.nids; i++) {
		int id = keyboard_ids.id[i];

		adb_get_infos(id, &default_id, &org_handler_id);

		/* turn off all leds */
		adb_request(&req, NULL, ADBREQ_SYNC, 3,
			    ADB_WRITEREG(id, KEYB_LEDREG), 0xff, 0xff);

		/* Enable full feature set of the keyboard
		   ->get it to send separate codes for left and right shift,
		   control, option keys */
#if 0		/* handler 5 doesn't send separate codes for R modifiers */
		if (adb_try_handler_change(id, 5))
			printk("ADB keyboard at %d, handler set to 5\n", id);
		else
#endif
		if (adb_try_handler_change(id, 3))
			printk("ADB keyboard at %d, handler set to 3\n", id);
		else
			printk("ADB keyboard at %d, handler 1\n", id);

		adb_get_infos(id, &default_id, &cur_handler_id);
		reg |= adbhid_input_reregister(id, default_id, org_handler_id,
					       cur_handler_id, 0);
	}

	for (i = 0; i < buttons_ids.nids; i++) {
		int id = buttons_ids.id[i];

		adb_get_infos(id, &default_id, &org_handler_id);
		reg |= adbhid_input_reregister(id, default_id, org_handler_id,
					       org_handler_id, 0);
	}

	/* Try to switch all mice to handler 4, or 2 for three-button
	   mode and full resolution. */
	for (i = 0; i < mouse_ids.nids; i++) {
		int id = mouse_ids.id[i];
		int mouse_kind;

		adb_get_infos(id, &default_id, &org_handler_id);

		if (adb_try_handler_change(id, 4)) {
			printk("ADB mouse at %d, handler set to 4", id);
			mouse_kind = ADBMOUSE_EXTENDED;
		}
		else if (adb_try_handler_change(id, 0x2F)) {
			printk("ADB mouse at %d, handler set to 0x2F", id);
			mouse_kind = ADBMOUSE_MICROSPEED;
		}
		else if (adb_try_handler_change(id, 0x42)) {
			printk("ADB mouse at %d, handler set to 0x42", id);
			mouse_kind = ADBMOUSE_TRACKBALLPRO;
		}
		else if (adb_try_handler_change(id, 0x66)) {
			printk("ADB mouse at %d, handler set to 0x66", id);
			mouse_kind = ADBMOUSE_MICROSPEED;
		}
		else if (adb_try_handler_change(id, 0x5F)) {
			printk("ADB mouse at %d, handler set to 0x5F", id);
			mouse_kind = ADBMOUSE_MICROSPEED;
		}
		else if (adb_try_handler_change(id, 3)) {
			printk("ADB mouse at %d, handler set to 3", id);
			mouse_kind = ADBMOUSE_MS_A3;
		}
		else if (adb_try_handler_change(id, 2)) {
			printk("ADB mouse at %d, handler set to 2", id);
			mouse_kind = ADBMOUSE_STANDARD_200;
		}
		else {
			printk("ADB mouse at %d, handler 1", id);
			mouse_kind = ADBMOUSE_STANDARD_100;
		}

		if ((mouse_kind == ADBMOUSE_TRACKBALLPRO)
		    || (mouse_kind == ADBMOUSE_MICROSPEED)) {
			init_microspeed(id);
		} else if (mouse_kind == ADBMOUSE_MS_A3) {
			init_ms_a3(id);
		} else if (mouse_kind ==  ADBMOUSE_EXTENDED) {
			/*
			 * Register 1 is usually used for device
			 * identification.  Here, we try to identify
			 * a known device and call the appropriate
			 * init function.
			 */
			adb_request(&req, NULL, ADBREQ_SYNC | ADBREQ_REPLY, 1,
				    ADB_READREG(id, 1));

			if ((req.reply_len) &&
			    (req.reply[1] == 0x9a) && ((req.reply[2] == 0x21)
			    	|| (req.reply[2] == 0x20))) {
				mouse_kind = ADBMOUSE_TRACKBALL;
				init_trackball(id);
			}
			else if ((req.reply_len >= 4) &&
			    (req.reply[1] == 0x74) && (req.reply[2] == 0x70) &&
			    (req.reply[3] == 0x61) && (req.reply[4] == 0x64)) {
				mouse_kind = ADBMOUSE_TRACKPAD;
				init_trackpad(id);
			}
			else if ((req.reply_len >= 4) &&
			    (req.reply[1] == 0x4b) && (req.reply[2] == 0x4d) &&
			    (req.reply[3] == 0x4c) && (req.reply[4] == 0x31)) {
				mouse_kind = ADBMOUSE_TURBOMOUSE5;
				init_turbomouse(id);
			}
			else if ((req.reply_len == 9) &&
			    (req.reply[1] == 0x4b) && (req.reply[2] == 0x4f) &&
			    (req.reply[3] == 0x49) && (req.reply[4] == 0x54)) {
				if (adb_try_handler_change(id, 0x42)) {
					printk("\nADB MacAlly 2-button mouse at %d, handler set to 0x42", id);
					mouse_kind = ADBMOUSE_MACALLY2;
				}
			}
		}
		printk("\n");

		adb_get_infos(id, &default_id, &cur_handler_id);
		reg |= adbhid_input_reregister(id, default_id, org_handler_id,
					       cur_handler_id, mouse_kind);
	}
	adbhid_input_devcleanup(reg);
}