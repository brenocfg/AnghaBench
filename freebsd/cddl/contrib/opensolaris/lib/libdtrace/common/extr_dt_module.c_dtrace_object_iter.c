#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_objinfo_t ;
typedef  int (* dtrace_obj_f ) (TYPE_1__*,int /*<<< orphan*/ ,void*) ;
struct TYPE_6__ {int /*<<< orphan*/  const dt_modlist; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_module_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dt_list_next (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dt_module_info (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

int
dtrace_object_iter(dtrace_hdl_t *dtp, dtrace_obj_f *func, void *data)
{
	const dt_module_t *dmp = dt_list_next(&dtp->dt_modlist);
	dtrace_objinfo_t dto;
	int rv;

	for (; dmp != NULL; dmp = dt_list_next(dmp)) {
		if ((rv = (*func)(dtp, dt_module_info(dmp, &dto), data)) != 0)
			return (rv);
	}

	return (0);
}