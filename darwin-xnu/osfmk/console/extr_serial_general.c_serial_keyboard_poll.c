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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_UNINT ; 
 int _serial_getc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert_wait_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_interval_to_deadline (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cons_cinput (char) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 

void
serial_keyboard_poll(void)
{
	int chr;
	uint64_t next;

	while(1) {
		chr = _serial_getc(0, 1, 0, 1);	/* Get a character if there is one */
		if(chr < 0) /* The serial buffer is empty */
			break;
		cons_cinput((char)chr);			/* Buffer up the character */
	}

	clock_interval_to_deadline(16, 1000000, &next);	/* Get time of pop */

	assert_wait_deadline((event_t)serial_keyboard_poll, THREAD_UNINT, next);	/* Show we are "waiting" */
	thread_block((thread_continue_t)serial_keyboard_poll);	/* Wait for it */
	panic("serial_keyboard_poll: Shouldn't never ever get here...\n");
}