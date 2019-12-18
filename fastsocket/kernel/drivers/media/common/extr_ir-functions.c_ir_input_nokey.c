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
struct ir_input_state {scalar_t__ keypressed; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ir_input_key_event (struct input_dev*,struct ir_input_state*) ; 

void ir_input_nokey(struct input_dev *dev, struct ir_input_state *ir)
{
	if (ir->keypressed) {
		ir->keypressed = 0;
		ir_input_key_event(dev,ir);
	}
}