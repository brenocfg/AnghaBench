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
typedef  scalar_t__ u32 ;
struct ir_input_state {int keypressed; scalar_t__ keycode; scalar_t__ ir_raw; scalar_t__ ir_key; int /*<<< orphan*/  ir_codes; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IR_KEYCODE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ir_input_key_event (struct input_dev*,struct ir_input_state*) ; 

void ir_input_keydown(struct input_dev *dev, struct ir_input_state *ir,
		      u32 ir_key, u32 ir_raw)
{
	u32 keycode = IR_KEYCODE(ir->ir_codes, ir_key);

	if (ir->keypressed && ir->keycode != keycode) {
		ir->keypressed = 0;
		ir_input_key_event(dev,ir);
	}
	if (!ir->keypressed) {
		ir->ir_key  = ir_key;
		ir->ir_raw  = ir_raw;
		ir->keycode = keycode;
		ir->keypressed = 1;
		ir_input_key_event(dev,ir);
	}
}