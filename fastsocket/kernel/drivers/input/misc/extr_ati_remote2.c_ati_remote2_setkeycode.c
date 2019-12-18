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
struct input_dev {int /*<<< orphan*/  keybit; } ;
struct ati_remote2 {int mode_mask; int** keycode; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ATI_REMOTE2_MODES ; 
 int ATI_REMOTE2_PC ; 
 int EINVAL ; 
 int KEY_MAX ; 
 int KEY_RESERVED ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ati_remote2_key_table ; 
 int ati_remote2_lookup (int) ; 
 struct ati_remote2* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int ati_remote2_setkeycode(struct input_dev *idev, int scancode, int keycode)
{
	struct ati_remote2 *ar2 = input_get_drvdata(idev);
	int index, mode, old_keycode;

	mode = scancode >> 8;
	if (mode > ATI_REMOTE2_PC || !((1 << mode) & ar2->mode_mask))
		return -EINVAL;

	index = ati_remote2_lookup(scancode & 0xFF);
	if (index < 0)
		return -EINVAL;

	if (keycode < KEY_RESERVED || keycode > KEY_MAX)
		return -EINVAL;

	old_keycode = ar2->keycode[mode][index];
	ar2->keycode[mode][index] = keycode;
	__set_bit(keycode, idev->keybit);

	for (mode = 0; mode < ATI_REMOTE2_MODES; mode++) {
		for (index = 0; index < ARRAY_SIZE(ati_remote2_key_table); index++) {
			if (ar2->keycode[mode][index] == old_keycode)
				return 0;
		}
	}

	__clear_bit(old_keycode, idev->keybit);

	return 0;
}