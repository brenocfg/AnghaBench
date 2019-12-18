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
struct tomoyo_io_buffer {int read_step; int read_eof; int /*<<< orphan*/  write_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  strict_strtoul (int /*<<< orphan*/ ,int,unsigned long*) ; 

__attribute__((used)) static int tomoyo_write_pid(struct tomoyo_io_buffer *head)
{
	unsigned long pid;
	/* No error check. */
	strict_strtoul(head->write_buf, 10, &pid);
	head->read_step = (int) pid;
	head->read_eof = false;
	return 0;
}