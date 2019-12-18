#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ir_scancode_table {int size; TYPE_1__* scan; } ;
struct ir_input_state {int ir_type; int /*<<< orphan*/ * ir_codes; } ;
struct input_dev {int keycodesize; int keycodemax; int /*<<< orphan*/  evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/ * keycode; } ;
struct TYPE_2__ {int scancode; int /*<<< orphan*/  keycode; } ;
typedef  int /*<<< orphan*/  IR_KEYTAB_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REP ; 
 int IR_KEYTAB_SIZE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ repeat ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ir_input_init(struct input_dev *dev, struct ir_input_state *ir,
		   int ir_type, struct ir_scancode_table *ir_codes)
{
	int i;

	ir->ir_type = ir_type;

	memset(ir->ir_codes, 0, sizeof(ir->ir_codes));

	/*
	 * FIXME: This is a temporary workaround to use the new IR tables
	 * with the old approach. Later patches will replace this to a
	 * proper method
	 */

	if (ir_codes)
		for (i = 0; i < ir_codes->size; i++)
			if (ir_codes->scan[i].scancode < IR_KEYTAB_SIZE)
				ir->ir_codes[ir_codes->scan[i].scancode] = ir_codes->scan[i].keycode;

	dev->keycode     = ir->ir_codes;
	dev->keycodesize = sizeof(IR_KEYTAB_TYPE);
	dev->keycodemax  = IR_KEYTAB_SIZE;
	for (i = 0; i < IR_KEYTAB_SIZE; i++)
		set_bit(ir->ir_codes[i], dev->keybit);
	clear_bit(0, dev->keybit);

	set_bit(EV_KEY, dev->evbit);
	if (repeat)
		set_bit(EV_REP, dev->evbit);
}