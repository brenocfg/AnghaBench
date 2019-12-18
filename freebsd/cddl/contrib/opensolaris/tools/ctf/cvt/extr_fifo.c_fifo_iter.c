#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* fn_data; struct TYPE_4__* fn_next; } ;
typedef  TYPE_1__ fifonode_t ;
struct TYPE_5__ {TYPE_1__* f_head; } ;
typedef  TYPE_2__ fifo_t ;

/* Variables and functions */

int
fifo_iter(fifo_t *f, int (*iter)(void *data, void *arg), void *arg)
{
	fifonode_t *fn;
	int rc;
	int ret = 0;

	for (fn = f->f_head; fn; fn = fn->fn_next) {
		if ((rc = iter(fn->fn_data, arg)) < 0)
			return (-1);
		ret += rc;
	}

	return (ret);
}