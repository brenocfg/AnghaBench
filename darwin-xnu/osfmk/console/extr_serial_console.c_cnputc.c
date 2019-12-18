#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ PAB_active; scalar_t__ cpu_console_buf; } ;
typedef  TYPE_1__ cpu_data_t ;
struct TYPE_8__ {char* buf_base; char* buf_ptr; } ;
typedef  TYPE_2__ console_buf_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  write_lock; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _cnputs (char*,int) ; 
 int /*<<< orphan*/  console_restore_interrupts_state (scalar_t__) ; 
 TYPE_6__ console_ring ; 
 int /*<<< orphan*/  console_ring_lock_init () ; 
 int /*<<< orphan*/  console_ring_put (char) ; 
 scalar_t__ console_ring_space () ; 
 int /*<<< orphan*/  console_ring_try_empty () ; 
 scalar_t__ console_suspended ; 
 int /*<<< orphan*/  cpu_buffer_put (TYPE_2__*,char) ; 
 scalar_t__ cpu_buffer_size (TYPE_2__*) ; 
 TYPE_1__* current_cpu_datap () ; 
 scalar_t__ ml_set_interrupts_enabled (scalar_t__) ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int /*<<< orphan*/  simple_lock_try_lock_loop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

void
cnputc(char c)
{
	console_buf_t * cbp;
	cpu_data_t * cpu_data_p;
	boolean_t state;
	boolean_t needs_print = TRUE;
	char * cp;

restart:
	mp_disable_preemption();
	cpu_data_p = current_cpu_datap();
	cbp = (console_buf_t *)cpu_data_p->cpu_console_buf;
	if (console_suspended || cbp == NULL) {
		mp_enable_preemption();
		/* Put directly if console ring is not initialized or we're heading into suspend */
		_cnputs(&c, 1);
		return;
	}

#ifndef __x86_64__
	/* Is there a panic backtrace going on? */
	if (cpu_data_p->PAB_active) {
		/* If another processor was in the process of emptying the
		 * console ring buffer when it received the panic backtrace
		 * signal, that processor will be spinning in DebugXCall()
		 * waiting for the panicking processor to finish printing
		 * the backtrace. But panicking processor will never
		 * be able to obtain the ring buffer lock since it is
		 * owned by a processor that's spinning in DebugXCall().
		 * Blow away any locks that other processors may have on
		 * the console ring buffer so that the backtrace can
		 * complete.
		 */
		console_ring_lock_init();
	}
#endif /* __x86_64__ */

	state = ml_set_interrupts_enabled(FALSE);

	/*
	 * add to stack buf
	 * If the cpu buffer is full, we'll flush, then try
	 * another put.  If it fails a second time... screw
	 * it.
	 */
	if (needs_print && !cpu_buffer_put(cbp, c)) {
		simple_lock_try_lock_loop(&console_ring.write_lock);

		if (cpu_buffer_size(cbp) > console_ring_space()) {
			simple_unlock(&console_ring.write_lock);
			console_restore_interrupts_state(state);
			mp_enable_preemption();

			console_ring_try_empty();
			goto restart;
		}

		for (cp = cbp->buf_base; cp < cbp->buf_ptr; cp++)
			console_ring_put(*cp);
		cbp->buf_ptr = cbp->buf_base;
		simple_unlock(&console_ring.write_lock);

		cpu_buffer_put(cbp, c);
	}

	needs_print = FALSE;

	if (c != '\n') {
		console_restore_interrupts_state(state);
		mp_enable_preemption();
		return;
	}

	/* We printed a newline, time to flush the CPU buffer to the global buffer */
	simple_lock_try_lock_loop(&console_ring.write_lock);

	/*
	 * Is there enough space in the shared ring buffer?
	 * Try to empty if not.
	 * Note, we want the entire local buffer to fit to
	 * avoid another cpu interjecting.
	 */

	if (cpu_buffer_size(cbp) > console_ring_space()) {
		simple_unlock(&console_ring.write_lock);
		console_restore_interrupts_state(state);
		mp_enable_preemption();

		console_ring_try_empty();

		goto restart;
	}

	for (cp = cbp->buf_base; cp < cbp->buf_ptr; cp++)
		console_ring_put(*cp);

	cbp->buf_ptr = cbp->buf_base;
	simple_unlock(&console_ring.write_lock);

	console_restore_interrupts_state(state);
	mp_enable_preemption();

	console_ring_try_empty();

	return;
}