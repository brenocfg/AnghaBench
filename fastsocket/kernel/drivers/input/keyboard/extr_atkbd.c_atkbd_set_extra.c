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
struct input_dev {int dummy; } ;
struct atkbd {unsigned long extra; unsigned char set; struct input_dev* dev; int /*<<< orphan*/  write; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  atkbd_activate (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_reset_state (struct atkbd*) ; 
 void* atkbd_select_set (struct atkbd*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  atkbd_set_device_attrs (struct atkbd*) ; 
 int /*<<< orphan*/  atkbd_set_keycode_table (struct atkbd*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t atkbd_set_extra(struct atkbd *atkbd, const char *buf, size_t count)
{
	struct input_dev *old_dev, *new_dev;
	unsigned long value;
	int err;
	unsigned char old_extra, old_set;

	if (!atkbd->write)
		return -EIO;

	if (strict_strtoul(buf, 10, &value) || value > 1)
		return -EINVAL;

	if (atkbd->extra != value) {
		/*
		 * Since device's properties will change we need to
		 * unregister old device. But allocate and register
		 * new one first to make sure we have it.
		 */
		old_dev = atkbd->dev;
		old_extra = atkbd->extra;
		old_set = atkbd->set;

		new_dev = input_allocate_device();
		if (!new_dev)
			return -ENOMEM;

		atkbd->dev = new_dev;
		atkbd->set = atkbd_select_set(atkbd, atkbd->set, value);
		atkbd_reset_state(atkbd);
		atkbd_activate(atkbd);
		atkbd_set_keycode_table(atkbd);
		atkbd_set_device_attrs(atkbd);

		err = input_register_device(atkbd->dev);
		if (err) {
			input_free_device(new_dev);

			atkbd->dev = old_dev;
			atkbd->set = atkbd_select_set(atkbd, old_set, old_extra);
			atkbd_set_keycode_table(atkbd);
			atkbd_set_device_attrs(atkbd);

			return err;
		}
		input_unregister_device(old_dev);

	}
	return count;
}