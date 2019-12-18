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
struct pcc_acpi {int* keymap; } ;
struct input_dev {int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int KEY_MAX ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 struct pcc_acpi* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  keymap_get_by_keycode (struct pcc_acpi*,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcc_setkeycode(struct input_dev *dev, int scancode, int keycode)
{
	struct pcc_acpi *pcc = input_get_drvdata(dev);
	int oldkeycode;

	if (scancode >= ARRAY_SIZE(pcc->keymap))
		return -EINVAL;

	if (keycode < 0 || keycode > KEY_MAX)
		return -EINVAL;

	oldkeycode = pcc->keymap[scancode];
	pcc->keymap[scancode] = keycode;

	set_bit(keycode, dev->keybit);

	if (!keymap_get_by_keycode(pcc, oldkeycode))
		clear_bit(oldkeycode, dev->keybit);

	return 0;
}