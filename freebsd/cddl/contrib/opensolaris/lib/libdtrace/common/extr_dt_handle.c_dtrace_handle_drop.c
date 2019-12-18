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
struct TYPE_4__ {void* dt_droparg; int /*<<< orphan*/ * dt_drophdlr; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dtrace_handle_drop_f ;

/* Variables and functions */
 int /*<<< orphan*/  EALREADY ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
dtrace_handle_drop(dtrace_hdl_t *dtp, dtrace_handle_drop_f *hdlr, void *arg)
{
	if (dtp->dt_drophdlr != NULL)
		return (dt_set_errno(dtp, EALREADY));

	dtp->dt_drophdlr = hdlr;
	dtp->dt_droparg = arg;

	return (0);
}