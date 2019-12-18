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
struct saa7134_dev {struct saa7134_card_ir* remote; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct saa7134_card_ir {int running; int active; TYPE_1__ timer; scalar_t__ raw_decode; scalar_t__ polling; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ir_raw_decode_timer_end ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  saa7134_input_timer ; 
 int /*<<< orphan*/  setup_timer (TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int __saa7134_ir_start(void *priv)
{
	struct saa7134_dev *dev = priv;
	struct saa7134_card_ir *ir;

	if (!dev || !dev->remote)
		return -EINVAL;

	ir  = dev->remote;
	if (ir->running)
		return 0;

	ir->running = true;
	ir->active = false;

	if (ir->polling) {
		setup_timer(&ir->timer, saa7134_input_timer,
			    (unsigned long)dev);
		ir->timer.expires = jiffies + HZ;
		add_timer(&ir->timer);
	} else if (ir->raw_decode) {
		/* set timer_end for code completion */
		setup_timer(&ir->timer, ir_raw_decode_timer_end,
			    (unsigned long)dev);
	}

	return 0;
}