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
struct etrax_recv_buffer {int /*<<< orphan*/  error; scalar_t__ length; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 struct etrax_recv_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct etrax_recv_buffer *
alloc_recv_buffer(unsigned int size)
{
	struct etrax_recv_buffer *buffer;

	if (!(buffer = kmalloc(sizeof *buffer + size, GFP_ATOMIC)))
		return NULL;

	buffer->next = NULL;
	buffer->length = 0;
	buffer->error = TTY_NORMAL;

	return buffer;
}