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
struct scatterlist {int dummy; } ;
struct __kfifo {int mask; unsigned int esize; scalar_t__ data; } ;

/* Variables and functions */
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int setup_sgl_buf (struct scatterlist*,scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 

__attribute__((used)) static unsigned int setup_sgl(struct __kfifo *fifo, struct scatterlist *sgl,
		int nents, unsigned int len, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int l;
	unsigned int n;

	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		len *= esize;
	}
	l = min(len, size - off);

	n  = setup_sgl_buf(sgl, fifo->data + off, nents, l);
	n += setup_sgl_buf(sgl + n, fifo->data, nents - n, len - l);

	if (n)
		sg_mark_end(sgl + n - 1);
	return n;
}