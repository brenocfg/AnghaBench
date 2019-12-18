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
struct tty_struct {int dummy; } ;
struct etrax_recv_buffer {unsigned int length; int /*<<< orphan*/  error; scalar_t__ buffer; struct etrax_recv_buffer* next; } ;
struct TYPE_2__ {struct tty_struct* tty; } ;
struct e100_serial {unsigned int recv_cnt; int /*<<< orphan*/ * last_recv_buffer; struct etrax_recv_buffer* first_recv_buffer; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  kfree (struct etrax_recv_buffer*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_struct*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void flush_to_flip_buffer(struct e100_serial *info)
{
	struct tty_struct *tty;
	struct etrax_recv_buffer *buffer;
	unsigned long flags;

	local_irq_save(flags);
	tty = info->port.tty;

	if (!tty) {
		local_irq_restore(flags);
		return;
	}

	while ((buffer = info->first_recv_buffer) != NULL) {
		unsigned int count = buffer->length;

		tty_insert_flip_string(tty, buffer->buffer, count);
		info->recv_cnt -= count;

		if (count == buffer->length) {
			info->first_recv_buffer = buffer->next;
			kfree(buffer);
		} else {
			buffer->length -= count;
			memmove(buffer->buffer, buffer->buffer + count, buffer->length);
			buffer->error = TTY_NORMAL;
		}
	}

	if (!info->first_recv_buffer)
		info->last_recv_buffer = NULL;

	local_irq_restore(flags);

	/* This includes a check for low-latency */
	tty_flip_buffer_push(tty);
}