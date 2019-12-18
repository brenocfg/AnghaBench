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
struct print_buf {int size; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * crs; } ;

/* Variables and functions */

void tipc_printbuf_reset(struct print_buf *pb)
{
	if (pb->buf) {
		pb->crs = pb->buf;
		pb->buf[0] = 0;
		pb->buf[pb->size - 1] = ~0;
	}
}