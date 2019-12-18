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
struct kfifo {unsigned char* buffer; unsigned int size; int /*<<< orphan*/ * lock; scalar_t__ out; scalar_t__ in; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct kfifo* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 
 struct kfifo* kmalloc (int,int /*<<< orphan*/ ) ; 

struct kfifo *kfifo_init(unsigned char *buffer, unsigned int size,
			 gfp_t gfp_mask, spinlock_t *lock)
{
	struct kfifo *fifo;

	/* size must be a power of 2 */
	BUG_ON(!is_power_of_2(size));

	fifo = kmalloc(sizeof(struct kfifo), gfp_mask);
	if (!fifo)
		return ERR_PTR(-ENOMEM);

	fifo->buffer = buffer;
	fifo->size = size;
	fifo->in = fifo->out = 0;
	fifo->lock = lock;

	return fifo;
}