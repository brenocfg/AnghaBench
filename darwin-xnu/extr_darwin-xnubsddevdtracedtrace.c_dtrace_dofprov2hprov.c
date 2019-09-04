#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dtpa_args; int /*<<< orphan*/  dtpa_name; int /*<<< orphan*/  dtpa_func; int /*<<< orphan*/  dtpa_mod; int /*<<< orphan*/  dtpa_provider; } ;
struct TYPE_7__ {char* dthpv_provname; TYPE_1__ dthpv_pattr; } ;
typedef  TYPE_2__ dtrace_helper_provdesc_t ;
struct TYPE_8__ {int dofpv_name; int /*<<< orphan*/  dofpv_argsattr; int /*<<< orphan*/  dofpv_nameattr; int /*<<< orphan*/  dofpv_funcattr; int /*<<< orphan*/  dofpv_modattr; int /*<<< orphan*/  dofpv_provattr; } ;
typedef  TYPE_3__ dof_provider_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_dofattr2attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_dofprov2hprov(dtrace_helper_provdesc_t *hprov,
    const dof_provider_t *dofprov, char *strtab)
{
	hprov->dthpv_provname = strtab + dofprov->dofpv_name;
	dtrace_dofattr2attr(&hprov->dthpv_pattr.dtpa_provider,
	    dofprov->dofpv_provattr);
	dtrace_dofattr2attr(&hprov->dthpv_pattr.dtpa_mod,
	    dofprov->dofpv_modattr);
	dtrace_dofattr2attr(&hprov->dthpv_pattr.dtpa_func,
	    dofprov->dofpv_funcattr);
	dtrace_dofattr2attr(&hprov->dthpv_pattr.dtpa_name,
	    dofprov->dofpv_nameattr);
	dtrace_dofattr2attr(&hprov->dthpv_pattr.dtpa_args,
	    dofprov->dofpv_argsattr);
}