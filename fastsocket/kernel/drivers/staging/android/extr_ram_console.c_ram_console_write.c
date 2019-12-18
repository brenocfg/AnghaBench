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
struct ram_console_buffer {unsigned int start; unsigned int size; } ;
struct console {int dummy; } ;

/* Variables and functions */
 struct ram_console_buffer* ram_console_buffer ; 
 unsigned int ram_console_buffer_size ; 
 int /*<<< orphan*/  ram_console_update (char const*,unsigned int) ; 
 int /*<<< orphan*/  ram_console_update_header () ; 

__attribute__((used)) static void
ram_console_write(struct console *console, const char *s, unsigned int count)
{
	int rem;
	struct ram_console_buffer *buffer = ram_console_buffer;

	if (count > ram_console_buffer_size) {
		s += count - ram_console_buffer_size;
		count = ram_console_buffer_size;
	}
	rem = ram_console_buffer_size - buffer->start;
	if (rem < count) {
		ram_console_update(s, rem);
		s += rem;
		count -= rem;
		buffer->start = 0;
		buffer->size = ram_console_buffer_size;
	}
	ram_console_update(s, count);

	buffer->start += count;
	if (buffer->size < ram_console_buffer_size)
		buffer->size += count;
	ram_console_update_header();
}