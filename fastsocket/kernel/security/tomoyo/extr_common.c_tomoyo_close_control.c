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
struct tomoyo_io_buffer {struct tomoyo_io_buffer* write_buf; struct tomoyo_io_buffer* read_buf; } ;
struct file {struct tomoyo_io_buffer* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  tomoyo_free (struct tomoyo_io_buffer*) ; 

__attribute__((used)) static int tomoyo_close_control(struct file *file)
{
	struct tomoyo_io_buffer *head = file->private_data;

	/* Release memory used for policy I/O. */
	tomoyo_free(head->read_buf);
	head->read_buf = NULL;
	tomoyo_free(head->write_buf);
	head->write_buf = NULL;
	tomoyo_free(head);
	head = NULL;
	file->private_data = NULL;
	return 0;
}