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
struct bttv_ir {int /*<<< orphan*/  polling; scalar_t__ rc5_gpio; } ;
struct bttv {struct bttv_ir* remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_rc5_irq (struct bttv*) ; 
 int /*<<< orphan*/  ir_handle_key (struct bttv*) ; 

void bttv_input_irq(struct bttv *btv)
{
	struct bttv_ir *ir = btv->remote;

	if (ir->rc5_gpio)
		bttv_rc5_irq(btv);
	else if (!ir->polling)
		ir_handle_key(btv);
}