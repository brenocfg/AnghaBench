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
struct TYPE_4__ {int /*<<< orphan*/  dt_linktype; } ;
typedef  TYPE_1__ dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_LTYP_DOF ; 
 int /*<<< orphan*/  DT_LTYP_ELF ; 
 int /*<<< orphan*/  EDT_BADOPTVAL ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
dt_opt_linktype(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	if (arg == NULL)
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	if (strcasecmp(arg, "elf") == 0)
		dtp->dt_linktype = DT_LTYP_ELF;
	else if (strcasecmp(arg, "dof") == 0)
		dtp->dt_linktype = DT_LTYP_DOF;
	else
		return (dt_set_errno(dtp, EDT_BADOPTVAL));

	return (0);
}