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
struct TYPE_3__ {scalar_t__ len; scalar_t__ tail; scalar_t__ head; int n; int data; } ;
typedef  TYPE_1__ msnd_fifo ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int,int) ; 

int msnd_fifo_read(msnd_fifo *f, char *buf, size_t len)
{
	int count = 0;

	while ((count < len) && (f->len > 0)) {

		int nread;

		if (f->tail <= f->head) {
			nread = len - count;
			if (nread > f->n - f->head)
				nread = f->n - f->head;
		}
		else {
			nread = f->tail - f->head;
			if (nread > len - count)
				nread = len - count;
		}

		memcpy(buf, f->data + f->head, nread);

		count += nread;
		buf += nread;
		f->len -= nread;
		f->head += nread;
		f->head %= f->n;
	}

	return count;
}