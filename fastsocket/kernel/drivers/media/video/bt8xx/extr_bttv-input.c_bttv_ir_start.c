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
struct TYPE_3__ {scalar_t__ expires; } ;
struct bttv_ir {int shift_by; int start; int addr; int /*<<< orphan*/  rc5_remote_gap; TYPE_1__ timer; scalar_t__ rc5_gpio; scalar_t__ polling; } ;
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  bttv_input_timer ; 
 int /*<<< orphan*/  bttv_rc5_timer_end ; 
 int /*<<< orphan*/  ir_rc5_remote_gap ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  setup_timer (TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void bttv_ir_start(struct bttv *btv, struct bttv_ir *ir)
{
	if (ir->polling) {
		setup_timer(&ir->timer, bttv_input_timer, (unsigned long)btv);
		ir->timer.expires  = jiffies + msecs_to_jiffies(1000);
		add_timer(&ir->timer);
	} else if (ir->rc5_gpio) {
		/* set timer_end for code completion */
		setup_timer(&ir->timer, bttv_rc5_timer_end, (unsigned long)ir);
		ir->shift_by = 1;
		ir->start = 3;
		ir->addr = 0x0;
		ir->rc5_remote_gap = ir_rc5_remote_gap;
	}
}