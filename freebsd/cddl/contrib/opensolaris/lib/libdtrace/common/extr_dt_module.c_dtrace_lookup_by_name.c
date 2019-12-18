#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct TYPE_23__ {char const* dts_name; int dts_id; int /*<<< orphan*/  dts_object; } ;
typedef  TYPE_3__ dtrace_syminfo_t ;
struct TYPE_22__ {scalar_t__ cts_data; } ;
struct TYPE_25__ {int dm_flags; int /*<<< orphan*/  dm_name; int /*<<< orphan*/ * dm_extern; TYPE_2__ dm_strtab; TYPE_1__* dm_ops; } ;
struct TYPE_24__ {int dt_nmods; TYPE_5__ dt_modlist; } ;
typedef  TYPE_4__ dtrace_hdl_t ;
typedef  TYPE_5__ dt_module_t ;
struct TYPE_26__ {char const* di_name; int di_id; int /*<<< orphan*/  di_type; int /*<<< orphan*/  di_ctfp; } ;
typedef  TYPE_6__ dt_ident_t ;
struct TYPE_27__ {uintptr_t st_name; int /*<<< orphan*/  st_size; scalar_t__ st_value; int /*<<< orphan*/  st_shndx; scalar_t__ st_other; int /*<<< orphan*/  st_info; } ;
struct TYPE_21__ {int /*<<< orphan*/ * (* do_symname ) (TYPE_5__*,char const*,TYPE_7__*,int*) ;} ;
typedef  TYPE_7__ GElf_Sym ;

/* Variables and functions */
 char const* DTRACE_OBJ_EVERY ; 
 char const* DTRACE_OBJ_KMODS ; 
 char const* DTRACE_OBJ_UMODS ; 
 int DT_DM_KERNEL ; 
 int /*<<< orphan*/  EDT_NOSYM ; 
 int /*<<< orphan*/  GELF_ST_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHN_UNDEF ; 
 int /*<<< orphan*/  STB_GLOBAL ; 
 int /*<<< orphan*/  STT_NOTYPE ; 
 int /*<<< orphan*/  ctf_type_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* dt_idhash_lookup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_5__* dt_list_next (TYPE_5__*) ; 
 TYPE_5__* dt_module_from_object (TYPE_4__*,char const*) ; 
 int dt_module_load (TYPE_4__*,TYPE_5__*) ; 
 int dt_set_errno (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_5__*,char const*,TYPE_7__*,int*) ; 

int
dtrace_lookup_by_name(dtrace_hdl_t *dtp, const char *object, const char *name,
    GElf_Sym *symp, dtrace_syminfo_t *sip)
{
	dt_module_t *dmp;
	dt_ident_t *idp;
	uint_t n, id;
	GElf_Sym sym;

	uint_t mask = 0; /* mask of dt_module flags to match */
	uint_t bits = 0; /* flag bits that must be present */

	if (object != DTRACE_OBJ_EVERY &&
	    object != DTRACE_OBJ_KMODS &&
	    object != DTRACE_OBJ_UMODS) {
		if ((dmp = dt_module_from_object(dtp, object)) == NULL)
			return (-1); /* dt_errno is set for us */

		if (dt_module_load(dtp, dmp) == -1)
			return (-1); /* dt_errno is set for us */
		n = 1;

	} else {
		if (object == DTRACE_OBJ_KMODS)
			mask = bits = DT_DM_KERNEL;
		else if (object == DTRACE_OBJ_UMODS)
			mask = DT_DM_KERNEL;

		dmp = dt_list_next(&dtp->dt_modlist);
		n = dtp->dt_nmods;
	}

	if (symp == NULL)
		symp = &sym;

	for (; n > 0; n--, dmp = dt_list_next(dmp)) {
		if ((dmp->dm_flags & mask) != bits)
			continue; /* failed to match required attributes */

		if (dt_module_load(dtp, dmp) == -1)
			continue; /* failed to load symbol table */

		if (dmp->dm_ops->do_symname(dmp, name, symp, &id) != NULL) {
			if (sip != NULL) {
				sip->dts_object = dmp->dm_name;
				sip->dts_name = (const char *)
				    dmp->dm_strtab.cts_data + symp->st_name;
				sip->dts_id = id;
			}
			return (0);
		}

		if (dmp->dm_extern != NULL &&
		    (idp = dt_idhash_lookup(dmp->dm_extern, name)) != NULL) {
			if (symp != &sym) {
				symp->st_name = (uintptr_t)idp->di_name;
				symp->st_info =
				    GELF_ST_INFO(STB_GLOBAL, STT_NOTYPE);
				symp->st_other = 0;
				symp->st_shndx = SHN_UNDEF;
				symp->st_value = 0;
				symp->st_size =
				    ctf_type_size(idp->di_ctfp, idp->di_type);
			}

			if (sip != NULL) {
				sip->dts_object = dmp->dm_name;
				sip->dts_name = idp->di_name;
				sip->dts_id = idp->di_id;
			}

			return (0);
		}
	}

	return (dt_set_errno(dtp, EDT_NOSYM));
}