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
struct input_dev {int /*<<< orphan*/  dev; } ;
struct dc_kbd {int* keycode; int* new; int* old; struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 void* memchr (int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void dc_scan_kbd(struct dc_kbd *kbd)
{
	struct input_dev *dev = kbd->dev;
	void *ptr;
	int code, keycode;
	int i;

	for (i = 0; i < 8; i++) {
		code = i + 224;
		keycode = kbd->keycode[code];
		input_event(dev, EV_MSC, MSC_SCAN, code);
		input_report_key(dev, keycode, (kbd->new[0] >> i) & 1);
	}

	for (i = 2; i < 8; i++) {
		ptr = memchr(kbd->new + 2, kbd->old[i], 6);
		code = kbd->old[i];
		if (code > 3 && ptr == NULL) {
			keycode = kbd->keycode[code];
			if (keycode) {
				input_event(dev, EV_MSC, MSC_SCAN, code);
				input_report_key(dev, keycode, 0);
			} else
				dev_dbg(&dev->dev,
					"Unknown key (scancode %#x) released.",
					code);
		}
		ptr = memchr(kbd->old + 2, kbd->new[i], 6);
		code = kbd->new[i];
		if (code > 3 && ptr) {
			keycode = kbd->keycode[code];
			if (keycode) {
				input_event(dev, EV_MSC, MSC_SCAN, code);
				input_report_key(dev, keycode, 1);
			} else
				dev_dbg(&dev->dev,
					"Unknown key (scancode %#x) pressed.",
					code);
		}
	}
	input_sync(dev);
	memcpy(kbd->old, kbd->new, 8);
}