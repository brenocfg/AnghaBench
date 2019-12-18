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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_3__ {scalar_t__ dbu_err; scalar_t__ dbu_len; int /*<<< orphan*/ * dbu_ptr; void* dbu_buf; } ;
typedef  TYPE_1__ dt_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ *,void*) ; 

void *
dt_buf_claim(dtrace_hdl_t *dtp, dt_buf_t *bp)
{
	void *buf = bp->dbu_buf;

	if (bp->dbu_err != 0) {
		dt_free(dtp, buf);
		buf = NULL;
	}

	bp->dbu_buf = bp->dbu_ptr = NULL;
	bp->dbu_len = 0;

	return (buf);
}