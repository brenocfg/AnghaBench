#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_4__ {int /*<<< orphan*/  dbu_len; int /*<<< orphan*/  dbu_name; scalar_t__ dbu_err; int /*<<< orphan*/ * dbu_buf; int /*<<< orphan*/ * dbu_ptr; } ;
typedef  TYPE_1__ dt_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_buf_create (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dt_buf_reset(dtrace_hdl_t *dtp, dt_buf_t *bp)
{
	if ((bp->dbu_ptr = bp->dbu_buf) != NULL)
		bp->dbu_err = 0;
	else
		dt_buf_create(dtp, bp, bp->dbu_name, bp->dbu_len);
}