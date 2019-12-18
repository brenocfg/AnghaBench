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
struct TYPE_2__ {size_t memory_used; } ;
struct tty_struct {TYPE_1__ buf; } ;
struct tty_buffer {size_t size; char* char_buf_ptr; unsigned char* flag_buf_ptr; scalar_t__ data; scalar_t__ read; scalar_t__ commit; int /*<<< orphan*/ * next; scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct tty_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tty_buffer *tty_buffer_alloc(struct tty_struct *tty, size_t size)
{
	struct tty_buffer *p;

	if (tty->buf.memory_used + size > 65536)
		return NULL;
	p = kmalloc(sizeof(struct tty_buffer) + 2 * size, GFP_ATOMIC);
	if (p == NULL)
		return NULL;
	p->used = 0;
	p->size = size;
	p->next = NULL;
	p->commit = 0;
	p->read = 0;
	p->char_buf_ptr = (char *)(p->data);
	p->flag_buf_ptr = (unsigned char *)p->char_buf_ptr + size;
	tty->buf.memory_used += size;
	return p;
}