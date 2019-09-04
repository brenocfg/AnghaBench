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
struct console_printbuf_state {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_PB_CANBLOCK ; 
 int /*<<< orphan*/  CONS_PB_WRITE_NEWLINE ; 
 int /*<<< orphan*/  bzero (struct console_printbuf_state*,int) ; 

void
console_printbuf_state_init(struct console_printbuf_state * data, int write_on_newline, int can_block)
{
	if (data == NULL)
		return;
	bzero(data, sizeof(struct console_printbuf_state));
	if (write_on_newline)
		data->flags |= CONS_PB_WRITE_NEWLINE;
	if (can_block)
		data->flags |= CONS_PB_CANBLOCK;
}