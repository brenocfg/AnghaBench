#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* fn_next; void* fn_data; } ;
typedef  TYPE_1__ fifonode_t ;
struct TYPE_6__ {TYPE_1__* f_tail; TYPE_1__* f_head; } ;
typedef  TYPE_2__ fifo_t ;

/* Variables and functions */
 TYPE_1__* xmalloc (int) ; 

void
fifo_add(fifo_t *f, void *data)
{
	fifonode_t *fn = xmalloc(sizeof (fifonode_t));

	fn->fn_data = data;
	fn->fn_next = NULL;

	if (f->f_tail == NULL)
		f->f_head = f->f_tail = fn;
	else {
		f->f_tail->fn_next = fn;
		f->f_tail = fn;
	}
}