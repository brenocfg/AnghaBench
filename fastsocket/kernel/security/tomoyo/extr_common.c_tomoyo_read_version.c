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
struct tomoyo_io_buffer {int read_eof; } ;

/* Variables and functions */
 int /*<<< orphan*/  tomoyo_io_printf (struct tomoyo_io_buffer*,char*) ; 

__attribute__((used)) static int tomoyo_read_version(struct tomoyo_io_buffer *head)
{
	if (!head->read_eof) {
		tomoyo_io_printf(head, "2.2.0");
		head->read_eof = true;
	}
	return 0;
}