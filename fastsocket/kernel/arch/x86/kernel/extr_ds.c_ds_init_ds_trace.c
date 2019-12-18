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
struct ds_trace {size_t n; size_t size; unsigned int flags; void* ith; void* end; void* begin; void* top; } ;
typedef  enum ds_qualifier { ____Placeholder_ds_qualifier } ds_qualifier ;
struct TYPE_2__ {size_t* sizeof_rec; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS_ALIGNMENT ; 
 TYPE_1__ ds_cfg ; 

__attribute__((used)) static void ds_init_ds_trace(struct ds_trace *trace, enum ds_qualifier qual,
			     void *base, size_t size, size_t ith,
			     unsigned int flags) {
	unsigned long buffer, adj;

	/*
	 * Adjust the buffer address and size to meet alignment
	 * constraints:
	 * - buffer is double-word aligned
	 * - size is multiple of record size
	 *
	 * We checked the size at the very beginning; we have enough
	 * space to do the adjustment.
	 */
	buffer = (unsigned long)base;

	adj = ALIGN(buffer, DS_ALIGNMENT) - buffer;
	buffer += adj;
	size   -= adj;

	trace->n = size / ds_cfg.sizeof_rec[qual];
	trace->size = ds_cfg.sizeof_rec[qual];

	size = (trace->n * trace->size);

	trace->begin = (void *)buffer;
	trace->top = trace->begin;
	trace->end = (void *)(buffer + size);
	/*
	 * The value for 'no threshold' is -1, which will set the
	 * threshold outside of the buffer, just like we want it.
	 */
	ith *= ds_cfg.sizeof_rec[qual];
	trace->ith = (void *)(buffer + size - ith);

	trace->flags = flags;
}