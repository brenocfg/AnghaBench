#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_14__ {int /*<<< orphan*/  dtt_type; int /*<<< orphan*/  dtt_ctfp; } ;
typedef  TYPE_1__ dtrace_typeinfo_t ;
struct TYPE_15__ {int /*<<< orphan*/  dts_id; int /*<<< orphan*/  dts_name; int /*<<< orphan*/  dts_object; } ;
typedef  TYPE_2__ dtrace_syminfo_t ;
struct TYPE_16__ {int /*<<< orphan*/  dt_gen; } ;
typedef  TYPE_3__ dtrace_hdl_t ;
struct TYPE_17__ {int /*<<< orphan*/  dm_name; int /*<<< orphan*/ * dm_extern; int /*<<< orphan*/  dm_nsymelems; } ;
typedef  TYPE_4__ dt_module_t ;
struct TYPE_18__ {int /*<<< orphan*/  di_type; int /*<<< orphan*/  di_ctfp; TYPE_2__* di_data; int /*<<< orphan*/  di_id; int /*<<< orphan*/  di_name; } ;
typedef  TYPE_5__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_IDENT_SYMBOL ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  EDT_SYMOFLOW ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  _dtrace_symattr ; 
 int /*<<< orphan*/ * dt_idhash_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* dt_idhash_insert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dt_idhash_nextid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_idops_thaw ; 
 int /*<<< orphan*/  dt_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 

dt_ident_t *
dt_module_extern(dtrace_hdl_t *dtp, dt_module_t *dmp,
    const char *name, const dtrace_typeinfo_t *tip)
{
	dtrace_syminfo_t *sip;
	dt_ident_t *idp;
	uint_t id;

	if (dmp->dm_extern == NULL && (dmp->dm_extern = dt_idhash_create(
	    "extern", NULL, dmp->dm_nsymelems, UINT_MAX)) == NULL) {
		(void) dt_set_errno(dtp, EDT_NOMEM);
		return (NULL);
	}

	if (dt_idhash_nextid(dmp->dm_extern, &id) == -1) {
		(void) dt_set_errno(dtp, EDT_SYMOFLOW);
		return (NULL);
	}

	if ((sip = malloc(sizeof (dtrace_syminfo_t))) == NULL) {
		(void) dt_set_errno(dtp, EDT_NOMEM);
		return (NULL);
	}

	idp = dt_idhash_insert(dmp->dm_extern, name, DT_IDENT_SYMBOL, 0, id,
	    _dtrace_symattr, 0, &dt_idops_thaw, NULL, dtp->dt_gen);

	if (idp == NULL) {
		(void) dt_set_errno(dtp, EDT_NOMEM);
		free(sip);
		return (NULL);
	}

	sip->dts_object = dmp->dm_name;
	sip->dts_name = idp->di_name;
	sip->dts_id = idp->di_id;

	idp->di_data = sip;
	idp->di_ctfp = tip->dtt_ctfp;
	idp->di_type = tip->dtt_type;

	return (idp);
}