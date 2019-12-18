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
struct pxa27x_keypad_platform_data {int matrix_key_map_size; unsigned int* matrix_key_map; int direct_key_num; unsigned short* direct_key_map; unsigned short rotary0_up_key; unsigned short rotary0_down_key; int rotary0_rel_code; unsigned short rotary1_up_key; unsigned short rotary1_down_key; int rotary1_rel_code; scalar_t__ enable_rotary1; scalar_t__ enable_rotary0; } ;
struct pxa27x_keypad {unsigned short* keycodes; int* rotary_rel_code; struct input_dev* input_dev; struct pxa27x_keypad_platform_data* pdata; } ;
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  relbit; } ;

/* Variables and functions */
 unsigned int KEY_COL (unsigned int) ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 unsigned int KEY_ROW (unsigned int) ; 
 unsigned short KEY_VAL (unsigned int) ; 
 int /*<<< orphan*/  MATRIX_ROW_SHIFT ; 
 unsigned int MATRIX_SCAN_CODE (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int MAX_MATRIX_KEY_NUM ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxa27x_keypad_build_keycode(struct pxa27x_keypad *keypad)
{
	struct pxa27x_keypad_platform_data *pdata = keypad->pdata;
	struct input_dev *input_dev = keypad->input_dev;
	unsigned short keycode;
	int i;

	for (i = 0; i < pdata->matrix_key_map_size; i++) {
		unsigned int key = pdata->matrix_key_map[i];
		unsigned int row = KEY_ROW(key);
		unsigned int col = KEY_COL(key);
		unsigned int scancode = MATRIX_SCAN_CODE(row, col,
							 MATRIX_ROW_SHIFT);

		keycode = KEY_VAL(key);
		keypad->keycodes[scancode] = keycode;
		__set_bit(keycode, input_dev->keybit);
	}

	for (i = 0; i < pdata->direct_key_num; i++) {
		keycode = pdata->direct_key_map[i];
		keypad->keycodes[MAX_MATRIX_KEY_NUM + i] = keycode;
		__set_bit(keycode, input_dev->keybit);
	}

	if (pdata->enable_rotary0) {
		if (pdata->rotary0_up_key && pdata->rotary0_down_key) {
			keycode = pdata->rotary0_up_key;
			keypad->keycodes[MAX_MATRIX_KEY_NUM + 0] = keycode;
			__set_bit(keycode, input_dev->keybit);

			keycode = pdata->rotary0_down_key;
			keypad->keycodes[MAX_MATRIX_KEY_NUM + 1] = keycode;
			__set_bit(keycode, input_dev->keybit);

			keypad->rotary_rel_code[0] = -1;
		} else {
			keypad->rotary_rel_code[0] = pdata->rotary0_rel_code;
			__set_bit(pdata->rotary0_rel_code, input_dev->relbit);
		}
	}

	if (pdata->enable_rotary1) {
		if (pdata->rotary1_up_key && pdata->rotary1_down_key) {
			keycode = pdata->rotary1_up_key;
			keypad->keycodes[MAX_MATRIX_KEY_NUM + 2] = keycode;
			__set_bit(keycode, input_dev->keybit);

			keycode = pdata->rotary1_down_key;
			keypad->keycodes[MAX_MATRIX_KEY_NUM + 3] = keycode;
			__set_bit(keycode, input_dev->keybit);

			keypad->rotary_rel_code[1] = -1;
		} else {
			keypad->rotary_rel_code[1] = pdata->rotary1_rel_code;
			__set_bit(pdata->rotary1_rel_code, input_dev->relbit);
		}
	}

	__clear_bit(KEY_RESERVED, input_dev->keybit);
}