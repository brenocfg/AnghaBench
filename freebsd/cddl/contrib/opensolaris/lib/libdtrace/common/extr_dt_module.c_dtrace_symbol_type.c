#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * dtt_object; int /*<<< orphan*/  dtt_type; int /*<<< orphan*/ * dtt_ctfp; scalar_t__ dtt_flags; } ;
typedef  TYPE_1__ dtrace_typeinfo_t ;
struct TYPE_20__ {int /*<<< orphan*/  dts_id; int /*<<< orphan*/  dts_name; int /*<<< orphan*/  dts_object; } ;
typedef  TYPE_2__ dtrace_syminfo_t ;
struct TYPE_21__ {int /*<<< orphan*/  dt_ctferr; } ;
typedef  TYPE_3__ dtrace_hdl_t ;
struct TYPE_22__ {int /*<<< orphan*/ * dm_name; int /*<<< orphan*/ * dm_ctfp; int /*<<< orphan*/ * dm_extern; } ;
typedef  TYPE_4__ dt_module_t ;
struct TYPE_23__ {int /*<<< orphan*/  di_type; int /*<<< orphan*/ * di_ctfp; } ;
typedef  TYPE_5__ dt_ident_t ;
struct TYPE_24__ {scalar_t__ st_shndx; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_6__ GElf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/ * DT_FPTR_CTFP (TYPE_3__*) ; 
 int /*<<< orphan*/  DT_FPTR_TYPE (TYPE_3__*) ; 
 int /*<<< orphan*/  EDT_CTF ; 
 int /*<<< orphan*/  EDT_NOMOD ; 
 int /*<<< orphan*/  EDT_NOSYM ; 
 scalar_t__ GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ STT_FUNC ; 
 int /*<<< orphan*/  ctf_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctf_lookup_by_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* dt_idhash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_module_getctf (TYPE_3__*,TYPE_4__*) ; 
 TYPE_4__* dt_module_lookup_by_name (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int dt_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
dtrace_symbol_type(dtrace_hdl_t *dtp, const GElf_Sym *symp,
    const dtrace_syminfo_t *sip, dtrace_typeinfo_t *tip)
{
	dt_module_t *dmp;

	tip->dtt_object = NULL;
	tip->dtt_ctfp = NULL;
	tip->dtt_type = CTF_ERR;
	tip->dtt_flags = 0;

	if ((dmp = dt_module_lookup_by_name(dtp, sip->dts_object)) == NULL)
		return (dt_set_errno(dtp, EDT_NOMOD));

	if (symp->st_shndx == SHN_UNDEF && dmp->dm_extern != NULL) {
		dt_ident_t *idp =
		    dt_idhash_lookup(dmp->dm_extern, sip->dts_name);

		if (idp == NULL)
			return (dt_set_errno(dtp, EDT_NOSYM));

		tip->dtt_ctfp = idp->di_ctfp;
		tip->dtt_type = idp->di_type;

	} else if (GELF_ST_TYPE(symp->st_info) != STT_FUNC) {
		if (dt_module_getctf(dtp, dmp) == NULL)
			return (-1); /* errno is set for us */

		tip->dtt_ctfp = dmp->dm_ctfp;
		tip->dtt_type = ctf_lookup_by_symbol(dmp->dm_ctfp, sip->dts_id);

		if (tip->dtt_type == CTF_ERR) {
			dtp->dt_ctferr = ctf_errno(tip->dtt_ctfp);
			return (dt_set_errno(dtp, EDT_CTF));
		}

	} else {
		tip->dtt_ctfp = DT_FPTR_CTFP(dtp);
		tip->dtt_type = DT_FPTR_TYPE(dtp);
	}

	tip->dtt_object = dmp->dm_name;
	return (0);
}