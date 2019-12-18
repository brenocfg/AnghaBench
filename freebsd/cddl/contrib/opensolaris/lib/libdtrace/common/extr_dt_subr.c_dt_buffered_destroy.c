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
struct TYPE_3__ {scalar_t__ dt_buffered_size; scalar_t__ dt_buffered_offs; int /*<<< orphan*/ * dt_buffered_buf; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
dt_buffered_destroy(dtrace_hdl_t *dtp)
{
	free(dtp->dt_buffered_buf);
	dtp->dt_buffered_buf = NULL;
	dtp->dt_buffered_offs = 0;
	dtp->dt_buffered_size = 0;
}