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
struct tps_key_entry {int keycode; } ;
struct input_dev {int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int EINVAL ; 
 int KEY_MAX ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps_get_key_by_keycode (int) ; 
 struct tps_key_entry* tps_get_key_by_scancode (int) ; 

__attribute__((used)) static int topstar_setkeycode(struct input_dev *dev, int scancode, int keycode)
{
	struct tps_key_entry *key;
	int old_keycode;

	if (keycode < 0 || keycode > KEY_MAX)
		return -EINVAL;

	key = tps_get_key_by_scancode(scancode);

	if (!key)
		return -EINVAL;

	old_keycode = key->keycode;
	key->keycode = keycode;
	set_bit(keycode, dev->keybit);
	if (!tps_get_key_by_keycode(old_keycode))
		clear_bit(old_keycode, dev->keybit);
	return 0;
}