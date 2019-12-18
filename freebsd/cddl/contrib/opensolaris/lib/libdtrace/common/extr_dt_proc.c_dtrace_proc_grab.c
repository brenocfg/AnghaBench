#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ps_prochandle {int dummy; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_6__ {int /*<<< orphan*/  dt_macros; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_7__ {scalar_t__ di_id; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 TYPE_2__* dt_idhash_lookup (int /*<<< orphan*/ ,char*) ; 
 struct ps_prochandle* dt_proc_grab (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ) ; 

struct ps_prochandle *
dtrace_proc_grab(dtrace_hdl_t *dtp, pid_t pid, int flags)
{
	dt_ident_t *idp = dt_idhash_lookup(dtp->dt_macros, "target");
	struct ps_prochandle *P = dt_proc_grab(dtp, pid, flags, 0);

	if (P != NULL && idp != NULL && idp->di_id == 0)
		idp->di_id = pid; /* $target = grabbed pid */

	return (P);
}