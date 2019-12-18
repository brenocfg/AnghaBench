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
typedef  int u32 ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_2__ {int tv_sec; int tv_usec; } ;
struct card_ir {int last_bit; int code; int shift_by; scalar_t__ start; scalar_t__ addr; int last_rc5; int /*<<< orphan*/  timer_keyup; int /*<<< orphan*/  rc5_key_timeout; int /*<<< orphan*/  ir; int /*<<< orphan*/  dev; scalar_t__ active; TYPE_1__ base_time; } ;

/* Variables and functions */
 scalar_t__ RC5_ADDR (int) ; 
 int RC5_INSTR (int) ; 
 scalar_t__ RC5_START (int) ; 
 int RC5_TOGGLE (int) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  ir_input_keydown (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ir_input_nokey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ir_rc5_decode (int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void ir_rc5_timer_end(unsigned long data)
{
	struct card_ir *ir = (struct card_ir *)data;
	struct timeval tv;
	unsigned long current_jiffies, timeout;
	u32 gap;
	u32 rc5 = 0;

	/* get time */
	current_jiffies = jiffies;
	do_gettimeofday(&tv);

	/* avoid overflow with gap >1s */
	if (tv.tv_sec - ir->base_time.tv_sec > 1) {
		gap = 200000;
	} else {
		gap = 1000000 * (tv.tv_sec - ir->base_time.tv_sec) +
		    tv.tv_usec - ir->base_time.tv_usec;
	}

	/* signal we're ready to start a new code */
	ir->active = 0;

	/* Allow some timer jitter (RC5 is ~24ms anyway so this is ok) */
	if (gap < 28000) {
		dprintk(1, "ir-common: spurious timer_end\n");
		return;
	}

	if (ir->last_bit < 20) {
		/* ignore spurious codes (caused by light/other remotes) */
		dprintk(1, "ir-common: short code: %x\n", ir->code);
	} else {
		ir->code = (ir->code << ir->shift_by) | 1;
		rc5 = ir_rc5_decode(ir->code);

		/* two start bits? */
		if (RC5_START(rc5) != ir->start) {
			dprintk(1, "ir-common: rc5 start bits invalid: %u\n", RC5_START(rc5));

			/* right address? */
		} else if (RC5_ADDR(rc5) == ir->addr) {
			u32 toggle = RC5_TOGGLE(rc5);
			u32 instr = RC5_INSTR(rc5);

			/* Good code, decide if repeat/repress */
			if (toggle != RC5_TOGGLE(ir->last_rc5) ||
			    instr != RC5_INSTR(ir->last_rc5)) {
				dprintk(1, "ir-common: instruction %x, toggle %x\n", instr,
					toggle);
				ir_input_nokey(ir->dev, &ir->ir);
				ir_input_keydown(ir->dev, &ir->ir, instr,
						 instr);
			}

			/* Set/reset key-up timer */
			timeout = current_jiffies +
				  msecs_to_jiffies(ir->rc5_key_timeout);
			mod_timer(&ir->timer_keyup, timeout);

			/* Save code for repeat test */
			ir->last_rc5 = rc5;
		}
	}
}