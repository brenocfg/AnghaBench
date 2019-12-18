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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _cnputs (char*,int) ; 
 scalar_t__ console_output ; 
 int /*<<< orphan*/  console_restore_interrupts_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  console_write (char*,int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

void
cnputsusr(char *s, int size)
{

	if (size > 1) {
		console_write(s, size);
		return;
	}

	boolean_t state;

	/* Spin (with pre-emption enabled) waiting for console_ring_try_empty()
	 * to complete output. There is a small window here where we could
	 * end up with a stale value of console_output, but it's unlikely,
	 * and _cnputs(), which outputs to the console device, is internally
	 * synchronized. There's something of a conflict between the
	 * character-at-a-time (with pre-emption enabled) unbuffered
	 * output model here, and the buffered output from cnputc(),
	 * whose consumers include printf() ( which outputs a sequence
	 * with pre-emption disabled, and should be safe to call with
	 * interrupts off); we don't want to disable pre-emption indefinitely
	 * here, and spinlocks and mutexes are inappropriate.
	 */
	while (console_output != 0) {
		delay(1);
	}

	/*
	 * We disable interrupts to avoid issues caused by rendevous IPIs
	 * and an interruptible core holding the lock while an uninterruptible
	 * core wants it.  Stackshot is the prime example of this.
	 */
	state = ml_set_interrupts_enabled(FALSE);
	_cnputs(s, 1);
	console_restore_interrupts_state(state);
}