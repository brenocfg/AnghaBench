#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_14__ {int dtc_ctfmodel; } ;
struct TYPE_15__ {int /*<<< orphan*/  dt_ctferr; TYPE_1__ dt_conf; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_13__ {scalar_t__ cts_size; } ;
struct TYPE_16__ {int /*<<< orphan*/ * dm_ctfp; int /*<<< orphan*/  dm_name; int /*<<< orphan*/  dm_strtab; int /*<<< orphan*/  dm_symtab; TYPE_12__ dm_ctdata; int /*<<< orphan*/ * dm_ops; } ;
typedef  TYPE_3__ dt_module_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 int CTF_MODEL_ILP32 ; 
 int CTF_MODEL_LP64 ; 
 int /*<<< orphan*/  EDT_CTF ; 
 int /*<<< orphan*/  EDT_DATAMODEL ; 
 int /*<<< orphan*/  EDT_NOCTF ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/ * ctf_bufopen (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctf_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctf_errno (int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_import (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* ctf_parent_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctf_setmodel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ctf_setspecific (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dt_modops_64 ; 
 TYPE_3__* dt_module_create (TYPE_2__*,char const*) ; 
 scalar_t__ dt_module_load (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 

ctf_file_t *
dt_module_getctf(dtrace_hdl_t *dtp, dt_module_t *dmp)
{
	const char *parent;
	dt_module_t *pmp;
	ctf_file_t *pfp;
	int model;

	if (dmp->dm_ctfp != NULL || dt_module_load(dtp, dmp) != 0)
		return (dmp->dm_ctfp);

	if (dmp->dm_ops == &dt_modops_64)
		model = CTF_MODEL_LP64;
	else
		model = CTF_MODEL_ILP32;

	/*
	 * If the data model of the module does not match our program data
	 * model, then do not permit CTF from this module to be opened and
	 * returned to the compiler.  If we support mixed data models in the
	 * future for combined kernel/user tracing, this can be removed.
	 */
	if (dtp->dt_conf.dtc_ctfmodel != model) {
		(void) dt_set_errno(dtp, EDT_DATAMODEL);
		return (NULL);
	}

	if (dmp->dm_ctdata.cts_size == 0) {
		(void) dt_set_errno(dtp, EDT_NOCTF);
		return (NULL);
	}

	dmp->dm_ctfp = ctf_bufopen(&dmp->dm_ctdata,
	    &dmp->dm_symtab, &dmp->dm_strtab, &dtp->dt_ctferr);

	if (dmp->dm_ctfp == NULL) {
		(void) dt_set_errno(dtp, EDT_CTF);
		return (NULL);
	}

	(void) ctf_setmodel(dmp->dm_ctfp, model);
	ctf_setspecific(dmp->dm_ctfp, dmp);

	if ((parent = ctf_parent_name(dmp->dm_ctfp)) != NULL) {
		if ((pmp = dt_module_create(dtp, parent)) == NULL ||
		    (pfp = dt_module_getctf(dtp, pmp)) == NULL) {
			if (pmp == NULL)
				(void) dt_set_errno(dtp, EDT_NOMEM);
			goto err;
		}

		if (ctf_import(dmp->dm_ctfp, pfp) == CTF_ERR) {
			dtp->dt_ctferr = ctf_errno(dmp->dm_ctfp);
			(void) dt_set_errno(dtp, EDT_CTF);
			goto err;
		}
	}

	dt_dprintf("loaded CTF container for %s (%p)\n",
	    dmp->dm_name, (void *)dmp->dm_ctfp);

	return (dmp->dm_ctfp);

err:
	ctf_close(dmp->dm_ctfp);
	dmp->dm_ctfp = NULL;
	return (NULL);
}