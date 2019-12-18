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
struct print_buf {scalar_t__ buf; scalar_t__ crs; } ;

/* Variables and functions */

int tipc_printbuf_empty(struct print_buf *pb)
{
	return (!pb->buf || (pb->crs == pb->buf));
}