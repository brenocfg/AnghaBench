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
struct card_ir {int /*<<< orphan*/  ir; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  ir_input_nokey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ir_rc5_timer_keyup(unsigned long data)
{
	struct card_ir *ir = (struct card_ir *)data;

	dprintk(1, "ir-common: key released\n");
	ir_input_nokey(ir->dev, &ir->ir);
}