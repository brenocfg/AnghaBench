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
typedef  int /*<<< orphan*/  dtrace_setoptdata_t ;
struct TYPE_4__ {scalar_t__ (* dt_setopthdlr ) (int /*<<< orphan*/ *,void*) ;void* dt_setoptarg; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 scalar_t__ DTRACE_HANDLE_ABORT ; 
 int /*<<< orphan*/  EDT_DIRABORT ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,void*) ; 

int
dt_handle_setopt(dtrace_hdl_t *dtp, dtrace_setoptdata_t *data)
{
	void *arg = dtp->dt_setoptarg;

	if (dtp->dt_setopthdlr == NULL)
		return (0);

	if ((*dtp->dt_setopthdlr)(data, arg) == DTRACE_HANDLE_ABORT)
		return (dt_set_errno(dtp, EDT_DIRABORT));

	return (0);
}