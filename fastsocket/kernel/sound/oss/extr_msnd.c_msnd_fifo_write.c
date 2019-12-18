#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; scalar_t__ n; scalar_t__ head; scalar_t__ tail; int data; } ;
typedef  TYPE_1__ msnd_fifo ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int,char const*,int) ; 

int msnd_fifo_write(msnd_fifo *f, const char *buf, size_t len)
{
	int count = 0;

	while ((count < len) && (f->len != f->n)) {

		int nwritten;

		if (f->head <= f->tail) {
			nwritten = len - count;
			if (nwritten > f->n - f->tail)
				nwritten = f->n - f->tail;
		}
		else {
			nwritten = f->head - f->tail;
			if (nwritten > len - count)
				nwritten = len - count;
		}

		memcpy(f->data + f->tail, buf, nwritten);

		count += nwritten;
		buf += nwritten;
		f->len += nwritten;
		f->tail += nwritten;
		f->tail %= f->n;
	}

	return count;
}