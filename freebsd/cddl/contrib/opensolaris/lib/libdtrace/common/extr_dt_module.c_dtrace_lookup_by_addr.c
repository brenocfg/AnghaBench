#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_22__ {int (* dtv_lookup_by_addr ) (int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,TYPE_4__*) ;} ;
typedef  TYPE_3__ dtrace_vector_t ;
struct TYPE_23__ {char const* dts_name; int /*<<< orphan*/  dts_id; int /*<<< orphan*/  dts_object; } ;
typedef  TYPE_4__ dtrace_syminfo_t ;
struct TYPE_21__ {scalar_t__ cts_data; } ;
struct TYPE_25__ {scalar_t__ dm_text_va; scalar_t__ dm_text_size; scalar_t__ dm_data_va; scalar_t__ dm_data_size; scalar_t__ dm_bss_va; scalar_t__ dm_bss_size; TYPE_2__ dm_strtab; int /*<<< orphan*/  dm_name; TYPE_1__* dm_ops; } ;
struct TYPE_24__ {TYPE_6__ dt_modlist; int /*<<< orphan*/  dt_varg; TYPE_3__* dt_vector; } ;
typedef  TYPE_5__ dtrace_hdl_t ;
typedef  TYPE_6__ dt_module_t ;
struct TYPE_26__ {int st_name; } ;
struct TYPE_20__ {int /*<<< orphan*/ * (* do_symaddr ) (TYPE_6__*,scalar_t__,TYPE_7__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_7__ GElf_Sym ;
typedef  scalar_t__ GElf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOSYMADDR ; 
 TYPE_6__* dt_list_next (TYPE_6__*) ; 
 int dt_module_load (TYPE_5__*,TYPE_6__*) ; 
 int dt_set_errno (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * stub2 (TYPE_6__*,scalar_t__,TYPE_7__*,int /*<<< orphan*/ *) ; 

int
dtrace_lookup_by_addr(dtrace_hdl_t *dtp, GElf_Addr addr,
    GElf_Sym *symp, dtrace_syminfo_t *sip)
{
	dt_module_t *dmp;
	uint_t id;
	const dtrace_vector_t *v = dtp->dt_vector;

	if (v != NULL)
		return (v->dtv_lookup_by_addr(dtp->dt_varg, addr, symp, sip));

	for (dmp = dt_list_next(&dtp->dt_modlist); dmp != NULL;
	    dmp = dt_list_next(dmp)) {
		if (addr - dmp->dm_text_va < dmp->dm_text_size ||
		    addr - dmp->dm_data_va < dmp->dm_data_size ||
		    addr - dmp->dm_bss_va < dmp->dm_bss_size)
			break;
	}

	if (dmp == NULL)
		return (dt_set_errno(dtp, EDT_NOSYMADDR));

	if (dt_module_load(dtp, dmp) == -1)
		return (-1); /* dt_errno is set for us */

	if (symp != NULL) {
		if (dmp->dm_ops->do_symaddr(dmp, addr, symp, &id) == NULL)
			return (dt_set_errno(dtp, EDT_NOSYMADDR));
	}

	if (sip != NULL) {
		sip->dts_object = dmp->dm_name;

		if (symp != NULL) {
			sip->dts_name = (const char *)
			    dmp->dm_strtab.cts_data + symp->st_name;
			sip->dts_id = id;
		} else {
			sip->dts_name = NULL;
			sip->dts_id = 0;
		}
	}

	return (0);
}