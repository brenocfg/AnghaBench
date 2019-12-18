#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct dm355evm_keys {int /*<<< orphan*/  input; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int event; int keycode; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DM355EVM_MSP_INPUT_HIGH ; 
 int /*<<< orphan*/  DM355EVM_MSP_INPUT_LOW ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int KEY_UNKNOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 TYPE_1__* dm355evm_keys ; 
 int dm355evm_msp_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dm355evm_keys_irq(int irq, void *_keys)
{
	struct dm355evm_keys	*keys = _keys;
	int			status;

	/* For simplicity we ignore INPUT_COUNT and just read
	 * events until we get the "queue empty" indicator.
	 * Reading INPUT_LOW decrements the count.
	 */
	for (;;) {
		static u16	last_event;
		u16		event;
		int		keycode;
		int		i;

		status = dm355evm_msp_read(DM355EVM_MSP_INPUT_HIGH);
		if (status < 0) {
			dev_dbg(keys->dev, "input high err %d\n",
					status);
			break;
		}
		event = status << 8;

		status = dm355evm_msp_read(DM355EVM_MSP_INPUT_LOW);
		if (status < 0) {
			dev_dbg(keys->dev, "input low err %d\n",
					status);
			break;
		}
		event |= status;
		if (event == 0xdead)
			break;

		/* Press and release a button:  two events, same code.
		 * Press and hold (autorepeat), then release: N events
		 * (N > 2), same code.  For RC5 buttons the toggle bits
		 * distinguish (for example) "1-autorepeat" from "1 1";
		 * but PCB buttons don't support that bit.
		 *
		 * So we must synthesize release events.  We do that by
		 * mapping events to a press/release event pair; then
		 * to avoid adding extra events, skip the second event
		 * of each pair.
		 */
		if (event == last_event) {
			last_event = 0;
			continue;
		}
		last_event = event;

		/* ignore the RC5 toggle bit */
		event &= ~0x0800;

		/* find the key, or leave it as unknown */
		keycode = KEY_UNKNOWN;
		for (i = 0; i < ARRAY_SIZE(dm355evm_keys); i++) {
			if (dm355evm_keys[i].event != event)
				continue;
			keycode = dm355evm_keys[i].keycode;
			break;
		}
		dev_dbg(keys->dev,
			"input event 0x%04x--> keycode %d\n",
			event, keycode);

		/* report press + release */
		input_report_key(keys->input, keycode, 1);
		input_sync(keys->input);
		input_report_key(keys->input, keycode, 0);
		input_sync(keys->input);
	}
	return IRQ_HANDLED;
}