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
struct input_dev {int /*<<< orphan*/  led; } ;
struct hid_usage {scalar_t__ code; int /*<<< orphan*/  type; } ;
struct hid_device {int product; } ;
struct apple_sc {int fn_on; int quirks; int /*<<< orphan*/  pressed_numlock; int /*<<< orphan*/  pressed_fn; } ;
struct apple_key_translation {int flags; scalar_t__ to; } ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 int APPLE_FLAG_FKEY ; 
 int APPLE_ISO_KEYBOARD ; 
 int APPLE_NUMLOCK_EMULATION ; 
 scalar_t__ KEY_FN ; 
 scalar_t__ LED_NUML ; 
 struct apple_key_translation* apple_find_translation (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  apple_fn_keys ; 
 int /*<<< orphan*/  apple_iso_keyboard ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int fnmode ; 
 struct apple_sc* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  powerbook_fn_keys ; 
 int /*<<< orphan*/  powerbook_numlock_keys ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidinput_apple_event(struct hid_device *hid, struct input_dev *input,
		struct hid_usage *usage, __s32 value)
{
	struct apple_sc *asc = hid_get_drvdata(hid);
	const struct apple_key_translation *trans;

	if (usage->code == KEY_FN) {
		asc->fn_on = !!value;
		input_event(input, usage->type, usage->code, value);
		return 1;
	}

	if (fnmode) {
		int do_translate;

		trans = apple_find_translation((hid->product < 0x21d ||
					hid->product >= 0x300) ?
					powerbook_fn_keys : apple_fn_keys,
					usage->code);
		if (trans) {
			if (test_bit(usage->code, asc->pressed_fn))
				do_translate = 1;
			else if (trans->flags & APPLE_FLAG_FKEY)
				do_translate = (fnmode == 2 && asc->fn_on) ||
					(fnmode == 1 && !asc->fn_on);
			else
				do_translate = asc->fn_on;

			if (do_translate) {
				if (value)
					set_bit(usage->code, asc->pressed_fn);
				else
					clear_bit(usage->code, asc->pressed_fn);

				input_event(input, usage->type, trans->to,
						value);

				return 1;
			}
		}

		if (asc->quirks & APPLE_NUMLOCK_EMULATION &&
				(test_bit(usage->code, asc->pressed_numlock) ||
				test_bit(LED_NUML, input->led))) {
			trans = apple_find_translation(powerbook_numlock_keys,
					usage->code);

			if (trans) {
				if (value)
					set_bit(usage->code,
							asc->pressed_numlock);
				else
					clear_bit(usage->code,
							asc->pressed_numlock);

				input_event(input, usage->type, trans->to,
						value);
			}

			return 1;
		}
	}

	if (asc->quirks & APPLE_ISO_KEYBOARD) {
		trans = apple_find_translation(apple_iso_keyboard, usage->code);
		if (trans) {
			input_event(input, usage->type, trans->to, value);
			return 1;
		}
	}

	return 0;
}