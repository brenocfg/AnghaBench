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
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int len; int /*<<< orphan*/  write_lock; } ;

/* Variables and functions */
 int CPU_CONS_BUF_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  console_init () ; 
 int /*<<< orphan*/  console_restore_interrupts_state (int /*<<< orphan*/ ) ; 
 TYPE_1__ console_ring ; 
 int /*<<< orphan*/  console_ring_put (char) ; 
 int console_ring_space () ; 
 int /*<<< orphan*/  console_ring_try_empty () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_lock_try_lock_loop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

void
console_write(char * str, int size)
{
	console_init();
	int chunk_size = size;
	int i          = 0;

	if (size > console_ring.len)
		chunk_size = CPU_CONS_BUF_SIZE;

	while (size > 0) {
		boolean_t state = ml_set_interrupts_enabled(FALSE);

		simple_lock_try_lock_loop(&console_ring.write_lock);
		while (chunk_size > console_ring_space()) {
			simple_unlock(&console_ring.write_lock);
			console_restore_interrupts_state(state);

			console_ring_try_empty();

			state = ml_set_interrupts_enabled(FALSE);
			simple_lock_try_lock_loop(&console_ring.write_lock);
		}

		for (i = 0; i < chunk_size; i++)
			console_ring_put(str[i]);

		str = &str[i];
		size -= chunk_size;
		simple_unlock(&console_ring.write_lock);
		console_restore_interrupts_state(state);
	}

	console_ring_try_empty();
}