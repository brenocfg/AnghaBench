#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct TYPE_15__ {int /*<<< orphan*/  dtt_type; int /*<<< orphan*/ * dtt_ctfp; } ;
typedef  TYPE_1__ dtrace_typeinfo_t ;
struct TYPE_16__ {TYPE_3__* dt_pfdict; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_17__ {int pdi_nbuckets; TYPE_4__** pdi_buckets; } ;
typedef  TYPE_3__ dt_pfdict_t ;
struct TYPE_18__ {int /*<<< orphan*/ * pfc_name; int /*<<< orphan*/ * pfc_tstr; int /*<<< orphan*/ * pfc_ofmt; int /*<<< orphan*/ * pfc_print; int /*<<< orphan*/ * pfc_check; int /*<<< orphan*/  pfc_dtype; int /*<<< orphan*/  pfc_ctype; int /*<<< orphan*/ * pfc_dctfp; int /*<<< orphan*/ * pfc_cctfp; struct TYPE_18__* pfc_next; } ;
typedef  TYPE_4__ dt_pfconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  DTRACE_OBJ_CDEFS ; 
 int /*<<< orphan*/  DTRACE_OBJ_DDEFS ; 
 int /*<<< orphan*/  EDT_BADCONV ; 
 int /*<<< orphan*/  EDT_NOCONV ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 TYPE_4__* _dtrace_conversions ; 
 int _dtrace_strbuckets ; 
 int /*<<< orphan*/  bcopy (TYPE_4__ const*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  bzero (TYPE_4__**,int) ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_pfdict_destroy (TYPE_2__*) ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dt_strtab_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_lookup_by_type (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  pfcheck_type ; 

int
dt_pfdict_create(dtrace_hdl_t *dtp)
{
	uint_t n = _dtrace_strbuckets;
	const dt_pfconv_t *pfd;
	dt_pfdict_t *pdi;

	if ((pdi = malloc(sizeof (dt_pfdict_t))) == NULL ||
	    (pdi->pdi_buckets = malloc(sizeof (dt_pfconv_t *) * n)) == NULL) {
		free(pdi);
		return (dt_set_errno(dtp, EDT_NOMEM));
	}

	dtp->dt_pfdict = pdi;
	bzero(pdi->pdi_buckets, sizeof (dt_pfconv_t *) * n);
	pdi->pdi_nbuckets = n;

	for (pfd = _dtrace_conversions; pfd->pfc_name != NULL; pfd++) {
		dtrace_typeinfo_t dtt;
		dt_pfconv_t *pfc;
		uint_t h;

		if ((pfc = malloc(sizeof (dt_pfconv_t))) == NULL) {
			dt_pfdict_destroy(dtp);
			return (dt_set_errno(dtp, EDT_NOMEM));
		}

		bcopy(pfd, pfc, sizeof (dt_pfconv_t));
		h = dt_strtab_hash(pfc->pfc_name, NULL) % n;
		pfc->pfc_next = pdi->pdi_buckets[h];
		pdi->pdi_buckets[h] = pfc;

		dtt.dtt_ctfp = NULL;
		dtt.dtt_type = CTF_ERR;

		/*
		 * The "D" container or its parent must contain a definition of
		 * any type referenced by a printf conversion.  If none can be
		 * found, we fail to initialize the printf dictionary.
		 */
		if (pfc->pfc_check == &pfcheck_type && dtrace_lookup_by_type(
		    dtp, DTRACE_OBJ_DDEFS, pfc->pfc_tstr, &dtt) != 0) {
			dt_pfdict_destroy(dtp);
			return (dt_set_errno(dtp, EDT_NOCONV));
		}

		pfc->pfc_dctfp = dtt.dtt_ctfp;
		pfc->pfc_dtype = dtt.dtt_type;

		/*
		 * The "C" container may contain an alternate definition of an
		 * explicit conversion type.  If it does, use it; otherwise
		 * just set pfc_ctype to pfc_dtype so it is always valid.
		 */
		if (pfc->pfc_check == &pfcheck_type && dtrace_lookup_by_type(
		    dtp, DTRACE_OBJ_CDEFS, pfc->pfc_tstr, &dtt) == 0) {
			pfc->pfc_cctfp = dtt.dtt_ctfp;
			pfc->pfc_ctype = dtt.dtt_type;
		} else {
			pfc->pfc_cctfp = pfc->pfc_dctfp;
			pfc->pfc_ctype = pfc->pfc_dtype;
		}

		if (pfc->pfc_check == NULL || pfc->pfc_print == NULL ||
		    pfc->pfc_ofmt == NULL || pfc->pfc_tstr == NULL) {
			dt_pfdict_destroy(dtp);
			return (dt_set_errno(dtp, EDT_BADCONV));
		}

		dt_dprintf("loaded printf conversion %%%s\n", pfc->pfc_name);
	}

	return (0);
}