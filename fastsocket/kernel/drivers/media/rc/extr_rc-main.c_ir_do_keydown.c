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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rc_dev {int keypressed; int last_scancode; scalar_t__ last_toggle; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  last_keycode; int /*<<< orphan*/  input_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  IR_dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_do_keyup (struct rc_dev*) ; 

__attribute__((used)) static void ir_do_keydown(struct rc_dev *dev, int scancode,
			  u32 keycode, u8 toggle)
{
	input_event(dev->input_dev, EV_MSC, MSC_SCAN, scancode);

	/* Repeat event? */
	if (dev->keypressed &&
	    dev->last_scancode == scancode &&
	    dev->last_toggle == toggle)
		return;

	/* Release old keypress */
	ir_do_keyup(dev);

	dev->last_scancode = scancode;
	dev->last_toggle = toggle;
	dev->last_keycode = keycode;

	if (keycode == KEY_RESERVED)
		return;

	/* Register a keypress */
	dev->keypressed = true;
	IR_dprintk(1, "%s: key down event, key 0x%04x, scancode 0x%04x\n",
		   dev->input_name, keycode, scancode);
	input_report_key(dev->input_dev, dev->last_keycode, 1);
	input_sync(dev->input_dev);
}