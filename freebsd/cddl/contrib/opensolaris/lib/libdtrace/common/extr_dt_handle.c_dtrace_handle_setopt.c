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
struct TYPE_4__ {void* dt_setoptarg; int /*<<< orphan*/ * dt_setopthdlr; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dtrace_handle_setopt_f ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
dtrace_handle_setopt(dtrace_hdl_t *dtp, dtrace_handle_setopt_f *hdlr,
    void *arg)
{
	if (hdlr == NULL)
		return (dt_set_errno(dtp, EINVAL));

	dtp->dt_setopthdlr = hdlr;
	dtp->dt_setoptarg = arg;

	return (0);
}