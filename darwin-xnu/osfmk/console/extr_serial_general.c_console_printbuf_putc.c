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
struct console_printbuf_state {int total; int pos; int* str; int flags; } ;

/* Variables and functions */
 int CONS_PB_WRITE_NEWLINE ; 
 int SERIALMODE_SYNCDRAIN ; 
 int SERIAL_CONS_BUF_SIZE ; 
 int /*<<< orphan*/  console_write (char*,size_t) ; 
 int serialmode ; 

void
console_printbuf_putc(int ch, void * arg)
{
	struct console_printbuf_state * info = (struct console_printbuf_state *)arg;
	info->total += 1;
	if (info->pos < (SERIAL_CONS_BUF_SIZE - 1)) {
		info->str[info->pos] = ch;
		info->pos += 1;
	} else {
		/*
		 * when len(line) > SERIAL_CONS_BUF_SIZE, we truncate the message
		 * if boot-arg 'drain_uart_sync=1' is set, then
		 * drain all the buffer right now and append new ch
		 */
		if (serialmode & SERIALMODE_SYNCDRAIN) {
			info->str[info->pos] = '\0';
			console_write(info->str, info->pos);
			info->pos            = 0;
			info->str[info->pos] = ch;
			info->pos += 1;
		}
	}

	info->str[info->pos] = '\0';
	/* if newline, then try output to console */
	if (ch == '\n' && info->flags & CONS_PB_WRITE_NEWLINE) {
		console_write(info->str, info->pos);
		info->pos            = 0;
		info->str[info->pos] = '\0';
	}
}