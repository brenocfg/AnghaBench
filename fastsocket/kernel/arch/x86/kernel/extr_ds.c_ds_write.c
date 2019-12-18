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
struct ds_context {int /*<<< orphan*/  ds; } ;
typedef  enum ds_qualifier { ____Placeholder_ds_qualifier } ds_qualifier ;
struct TYPE_2__ {unsigned long* sizeof_rec; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ds_absolute_maximum ; 
 int /*<<< orphan*/  ds_buffer_base ; 
 TYPE_1__ ds_cfg ; 
 unsigned long ds_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_index ; 
 int /*<<< orphan*/  ds_interrupt_threshold ; 
 int /*<<< orphan*/  ds_overflow (struct ds_context*,int) ; 
 int /*<<< orphan*/  ds_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned long) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static int ds_write(struct ds_context *context, enum ds_qualifier qual,
		    const void *record, size_t size)
{
	int bytes_written = 0;

	if (!record)
		return -EINVAL;

	while (size) {
		unsigned long base, index, end, write_end, int_th;
		unsigned long write_size, adj_write_size;

		/*
		 * Write as much as possible without producing an
		 * overflow interrupt.
		 *
		 * Interrupt_threshold must either be
		 * - bigger than absolute_maximum or
		 * - point to a record between buffer_base and absolute_maximum
		 *
		 * Index points to a valid record.
		 */
		base   = ds_get(context->ds, qual, ds_buffer_base);
		index  = ds_get(context->ds, qual, ds_index);
		end    = ds_get(context->ds, qual, ds_absolute_maximum);
		int_th = ds_get(context->ds, qual, ds_interrupt_threshold);

		write_end = min(end, int_th);

		/*
		 * If we are already beyond the interrupt threshold,
		 * we fill the entire buffer.
		 */
		if (write_end <= index)
			write_end = end;

		if (write_end <= index)
			break;

		write_size = min((unsigned long) size, write_end - index);
		memcpy((void *)index, record, write_size);

		record = (const char *)record + write_size;
		size -= write_size;
		bytes_written += write_size;

		adj_write_size = write_size / ds_cfg.sizeof_rec[qual];
		adj_write_size *= ds_cfg.sizeof_rec[qual];

		/* Zero out trailing bytes. */
		memset((char *)index + write_size, 0,
		       adj_write_size - write_size);
		index += adj_write_size;

		if (index >= end)
			index = base;
		ds_set(context->ds, qual, ds_index, index);

		if (index >= int_th)
			ds_overflow(context, qual);
	}

	return bytes_written;
}