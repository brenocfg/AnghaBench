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
struct __kfifo {size_t esize; unsigned int mask; void* data; scalar_t__ out; scalar_t__ in; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 
 unsigned int rounddown_pow_of_two (unsigned int) ; 

int __kfifo_init(struct __kfifo *fifo, void *buffer,
		unsigned int size, size_t esize)
{
	size /= esize;

	if (!is_power_of_2(size))
		size = rounddown_pow_of_two(size);

	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = esize;
	fifo->data = buffer;

	if (size < 2) {
		fifo->mask = 0;
		return -EINVAL;
	}
	fifo->mask = size - 1;

	return 0;
}