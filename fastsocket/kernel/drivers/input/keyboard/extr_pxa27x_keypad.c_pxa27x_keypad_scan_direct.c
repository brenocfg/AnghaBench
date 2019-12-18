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
typedef  int uint32_t ;
struct pxa27x_keypad_platform_data {int direct_key_num; scalar_t__ enable_rotary1; scalar_t__ enable_rotary0; } ;
struct pxa27x_keypad {unsigned int direct_key_mask; unsigned int direct_key_state; int /*<<< orphan*/ * keycodes; struct input_dev* input_dev; struct pxa27x_keypad_platform_data* pdata; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  KPDK ; 
 unsigned int KPDK_DK (int) ; 
 int MAX_MATRIX_KEY_NUM ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int keypad_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa27x_keypad_scan_rotary (struct pxa27x_keypad*) ; 

__attribute__((used)) static void pxa27x_keypad_scan_direct(struct pxa27x_keypad *keypad)
{
	struct pxa27x_keypad_platform_data *pdata = keypad->pdata;
	struct input_dev *input_dev = keypad->input_dev;
	unsigned int new_state;
	uint32_t kpdk, bits_changed;
	int i;

	kpdk = keypad_readl(KPDK);

	if (pdata->enable_rotary0 || pdata->enable_rotary1)
		pxa27x_keypad_scan_rotary(keypad);

	new_state = KPDK_DK(kpdk) & keypad->direct_key_mask;
	bits_changed = keypad->direct_key_state ^ new_state;

	if (bits_changed == 0)
		return;

	for (i = 0; i < pdata->direct_key_num; i++) {
		if (bits_changed & (1 << i)) {
			int code = MAX_MATRIX_KEY_NUM + i;

			input_event(input_dev, EV_MSC, MSC_SCAN, code);
			input_report_key(input_dev, keypad->keycodes[code],
					 new_state & (1 << i));
		}
	}
	input_sync(input_dev);
	keypad->direct_key_state = new_state;
}