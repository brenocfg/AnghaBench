#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct error_system {int max_sub; TYPE_1__* subsystem; int /*<<< orphan*/  map_count; scalar_t__ map_table; } ;
typedef  int /*<<< orphan*/  mach_error_t ;
struct TYPE_2__ {scalar_t__ subsys_name; } ;

/* Variables and functions */
 struct error_system* _mach_errors ; 
 int /*<<< orphan*/  do_compat (int /*<<< orphan*/ *) ; 
 int err_get_sub (int /*<<< orphan*/ ) ; 
 int err_get_system (int /*<<< orphan*/ ) ; 
 int err_max_system ; 
 int err_sparse_mapit (int,scalar_t__,int /*<<< orphan*/ ) ; 

char *
mach_error_type(mach_error_t err)
{
	const struct error_system *sys_p;
	int sub, system;

	do_compat( &err );

	system = err_get_system(err);
	sys_p = &_mach_errors[system];
	sub = err_get_sub(err);

	if (system <= err_max_system && sys_p->map_table)
		sub = err_sparse_mapit(sub, sys_p->map_table, sys_p->map_count);

	if (system > err_max_system || sub >= sys_p->max_sub)
	    return((char *)"(?/?)");
	return (char *) (sys_p->subsystem[sub].subsys_name);
}