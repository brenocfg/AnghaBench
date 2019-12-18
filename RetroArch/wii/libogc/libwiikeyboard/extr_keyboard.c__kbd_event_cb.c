#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wscons_keymap {int* group1; void** group2; } ;
typedef  void* keysym_t ;
struct TYPE_6__ {scalar_t__ type; int modifiers; void* symbol; int /*<<< orphan*/  keycode; } ;
typedef  TYPE_1__ keyboard_event ;
struct TYPE_7__ {int type; int /*<<< orphan*/  keyCode; } ;
typedef  TYPE_2__ USBKeyboard_event ;
struct TYPE_8__ {void* symbol; int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 scalar_t__ KEYBOARD_DISCONNECTED ; 
 scalar_t__ KEYBOARD_PRESSED ; 
 scalar_t__ KEYBOARD_RELEASED ; 
#define  KS_Alt_L 147 
#define  KS_Alt_R 146 
#define  KS_Caps_Lock 145 
#define  KS_Control_L 144 
#define  KS_Control_R 143 
 int KS_GROUP (void*) ; 
#define  KS_GROUP_Ascii 142 
#define  KS_GROUP_Dead 141 
#define  KS_GROUP_Function 140 
#define  KS_GROUP_Keypad 139 
#define  KS_GROUP_Mod 138 
#define  KS_Hold_Screen 137 
#define  KS_Mode_Lock 136 
#define  KS_Mode_switch 135 
 void* KS_Multi_key ; 
#define  KS_Num_Lock 134 
#define  KS_Shift_L 133 
#define  KS_Shift_Lock 132 
#define  KS_Shift_R 131 
 int MAXHELD ; 
 int MOD_ANYCONTROL ; 
 int MOD_ANYSHIFT ; 
 int MOD_CAPSLOCK ; 
 int MOD_COMPOSE ; 
 int MOD_CONTROL_L ; 
 int MOD_CONTROL_R ; 
 int MOD_HOLDSCREEN ; 
 int MOD_META_L ; 
 int MOD_META_R ; 
 int MOD_MODELOCK ; 
 int MOD_MODESHIFT ; 
 int MOD_NUMLOCK ; 
 int MOD_ONESET (int,int) ; 
 int MOD_SHIFTLOCK ; 
 int MOD_SHIFT_L ; 
 int MOD_SHIFT_R ; 
#define  USBKEYBOARD_DISCONNECTED 130 
 int /*<<< orphan*/  USBKEYBOARD_LEDCAPS ; 
 int /*<<< orphan*/  USBKEYBOARD_LEDNUM ; 
 int /*<<< orphan*/  USBKEYBOARD_LEDSCROLL ; 
#define  USBKEYBOARD_PRESSED 129 
#define  USBKEYBOARD_RELEASED 128 
 int /*<<< orphan*/  USBKeyboard_SetLed (int /*<<< orphan*/ ,int) ; 
 void** _composebuf ; 
 int _composelen ; 
 TYPE_5__* _held ; 
 int /*<<< orphan*/  _kbd_addEvent (TYPE_1__*) ; 
 int _modifiers ; 
 int /*<<< orphan*/  _ukbd_keymapdata ; 
 void* ksym_upcase (void*) ; 
 int /*<<< orphan*/  update_modifier (scalar_t__,int,int) ; 
 void* wskbd_compose_value (void**) ; 
 int /*<<< orphan*/  wskbd_get_mapentry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wscons_keymap*) ; 

__attribute__((used)) static void _kbd_event_cb(USBKeyboard_event kevent)
{
	keyboard_event event;
	struct wscons_keymap kp;
	keysym_t *group;
	int gindex;
	keysym_t ksym;
	int i;

	switch (kevent.type) {
	case USBKEYBOARD_DISCONNECTED:
		event.type = KEYBOARD_DISCONNECTED;
		event.modifiers = 0;
		event.keycode = 0;
		event.symbol = 0;

		_kbd_addEvent(&event);

		return;

	case USBKEYBOARD_PRESSED:
		event.type = KEYBOARD_PRESSED;
		break;

	case USBKEYBOARD_RELEASED:
		event.type = KEYBOARD_RELEASED;
		break;

	default:
		return;
	}

	event.keycode = kevent.keyCode;

	wskbd_get_mapentry(&_ukbd_keymapdata, event.keycode, &kp);

	/* Now update modifiers */
	switch (kp.group1[0]) {
	case KS_Shift_L:
		update_modifier(event.type, 0, MOD_SHIFT_L);
		break;

	case KS_Shift_R:
		update_modifier(event.type, 0, MOD_SHIFT_R);
		break;

	case KS_Shift_Lock:
		update_modifier(event.type, 1, MOD_SHIFTLOCK);
		break;

	case KS_Caps_Lock:
		update_modifier(event.type, 1, MOD_CAPSLOCK);
		USBKeyboard_SetLed(USBKEYBOARD_LEDCAPS,
							MOD_ONESET(_modifiers, MOD_CAPSLOCK));
		break;

	case KS_Control_L:
		update_modifier(event.type, 0, MOD_CONTROL_L);
		break;

	case KS_Control_R:
		update_modifier(event.type, 0, MOD_CONTROL_R);
		break;

	case KS_Alt_L:
		update_modifier(event.type, 0, MOD_META_L);
		break;

	case KS_Alt_R:
		update_modifier(event.type, 0, MOD_META_R);
		break;

	case KS_Mode_switch:
		update_modifier(event.type, 0, MOD_MODESHIFT);
		break;

	case KS_Mode_Lock:
		update_modifier(event.type, 1, MOD_MODELOCK);
		break;

	case KS_Num_Lock:
		update_modifier(event.type, 1, MOD_NUMLOCK);
		USBKeyboard_SetLed(USBKEYBOARD_LEDNUM,
							MOD_ONESET(_modifiers, MOD_NUMLOCK));
		break;

	case KS_Hold_Screen:
		update_modifier(event.type, 1, MOD_HOLDSCREEN);
		USBKeyboard_SetLed(USBKEYBOARD_LEDSCROLL,
							MOD_ONESET(_modifiers, MOD_HOLDSCREEN));
		break;
	}

	/* Get the keysym */
	if (_modifiers & (MOD_MODESHIFT|MOD_MODELOCK) &&
	    !MOD_ONESET(_modifiers, MOD_ANYCONTROL))
		group = &kp.group2[0];
	else
		group = &kp.group1[0];

	if ((_modifiers & MOD_NUMLOCK) &&
	    KS_GROUP(group[1]) == KS_GROUP_Keypad) {
		gindex = !MOD_ONESET(_modifiers, MOD_ANYSHIFT);
		ksym = group[gindex];
	} else {
		/* CAPS alone should only affect letter keys */
		if ((_modifiers & (MOD_CAPSLOCK | MOD_ANYSHIFT)) ==
		    MOD_CAPSLOCK) {
			gindex = 0;
			ksym = ksym_upcase(group[0]);
		} else {
			gindex = MOD_ONESET(_modifiers, MOD_ANYSHIFT);
			ksym = group[gindex];
		}
	}

	/* Process compose sequence and dead accents */
	switch (KS_GROUP(ksym)) {
	case KS_GROUP_Mod:
		if (ksym == KS_Multi_key) {
			update_modifier(KEYBOARD_PRESSED, 0, MOD_COMPOSE);
			_composelen = 2;
		}
		break;

	case KS_GROUP_Dead:
		if (event.type != KEYBOARD_PRESSED)
			return;

		if (_composelen == 0) {
			update_modifier(KEYBOARD_PRESSED, 0, MOD_COMPOSE);
			_composelen = 1;
			_composebuf[0] = ksym;

			return;
		}
		break;
	}

	if ((event.type == KEYBOARD_PRESSED) && (_composelen > 0)) {
		/*
		 * If the compose key also serves as AltGr (i.e. set to both
		 * KS_Multi_key and KS_Mode_switch), and would provide a valid,
		 * distinct combination as AltGr, leave compose mode.
		 */
		if (_composelen == 2 && group == &kp.group2[0]) {
			if (kp.group1[gindex] != kp.group2[gindex])
				_composelen = 0;
		}

		if (_composelen != 0) {
			_composebuf[2 - _composelen] = ksym;
			if (--_composelen == 0) {
				ksym = wskbd_compose_value(_composebuf);
				update_modifier(KEYBOARD_RELEASED, 0, MOD_COMPOSE);
			} else {
				return;
			}
		}
	}

	// store up to MAXHELD pressed events to match the symbol for release
	switch (KS_GROUP(ksym)) {
	case KS_GROUP_Ascii:
	case KS_GROUP_Keypad:
	case KS_GROUP_Function:
		if (event.type == KEYBOARD_PRESSED) {
			for (i = 0; i < MAXHELD; ++i) {
				if (_held[i].keycode == 0) {
					_held[i].keycode = event.keycode;
					_held[i].symbol = ksym;

					break;
				}
			}
		} else {
			for (i = 0; i < MAXHELD; ++i) {
				if (_held[i].keycode == event.keycode) {
					ksym = _held[i].symbol;
					_held[i].keycode = 0;
					_held[i].symbol = 0;

					break;
				}
			}
		}

		break;
	}

	event.symbol = ksym;
	event.modifiers = _modifiers;

	_kbd_addEvent(&event);

	return;
}