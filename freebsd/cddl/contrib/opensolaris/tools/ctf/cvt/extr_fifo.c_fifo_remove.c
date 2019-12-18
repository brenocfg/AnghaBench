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
struct TYPE_6__ {int /*<<< orphan*/ * f_tail; TYPE_1__* f_head; } ;
typedef  TYPE_2__ fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void *
fifo_remove(fifo_t *f)
{
	fifonode_t *fn;
	void *data;

	if ((fn = f->f_head) == NULL)
		return (NULL);

	data = fn->fn_data;
	if ((f->f_head = fn->fn_next) == NULL)
		f->f_tail = NULL;

	free(fn);

	return (data);
}