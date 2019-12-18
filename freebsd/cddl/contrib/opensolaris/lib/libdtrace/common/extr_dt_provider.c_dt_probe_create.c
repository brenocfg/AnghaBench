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
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  dtrace_typeinfo_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_15__ {char const* pr_name; TYPE_3__** pr_nargv; TYPE_1__* pr_argv; TYPE_3__** pr_xargv; scalar_t__* pr_mapping; scalar_t__ pr_argc; scalar_t__ pr_xargc; scalar_t__ pr_nargc; int /*<<< orphan*/ * pr_inst; TYPE_3__* pr_xargs; TYPE_3__* pr_nargs; TYPE_5__* pr_ident; int /*<<< orphan*/ * pr_pvp; } ;
typedef  TYPE_2__ dt_probe_t ;
struct TYPE_16__ {struct TYPE_16__* dn_list; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; int /*<<< orphan*/ * dn_string; } ;
typedef  TYPE_3__ dt_node_t ;
struct TYPE_17__ {int /*<<< orphan*/ * dm_name; } ;
typedef  TYPE_4__ dt_module_t ;
struct TYPE_18__ {scalar_t__ di_kind; TYPE_2__* di_data; int /*<<< orphan*/  di_name; } ;
typedef  TYPE_5__ dt_ident_t ;
struct TYPE_14__ {int /*<<< orphan*/  dtt_type; int /*<<< orphan*/  dtt_ctfp; int /*<<< orphan*/ * dtt_object; } ;

/* Variables and functions */
 scalar_t__ DT_IDENT_PROBE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* dt_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* dt_module_lookup_by_ctf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_probe_argmap (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dt_probe_destroy (TYPE_2__*) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 

dt_probe_t *
dt_probe_create(dtrace_hdl_t *dtp, dt_ident_t *idp, int protoc,
    dt_node_t *nargs, uint_t nargc, dt_node_t *xargs, uint_t xargc)
{
	dt_module_t *dmp;
	dt_probe_t *prp;
	const char *p;
	uint_t i;

	assert(idp->di_kind == DT_IDENT_PROBE);
	assert(idp->di_data == NULL);

	/*
	 * If only a single prototype is given, set xargc/s to nargc/s to
	 * simplify subsequent use.  Note that we can have one or both of nargs
	 * and xargs be specified but set to NULL, indicating a void prototype.
	 */
	if (protoc < 2) {
		assert(xargs == NULL);
		assert(xargc == 0);
		xargs = nargs;
		xargc = nargc;
	}

	if ((prp = dt_alloc(dtp, sizeof (dt_probe_t))) == NULL)
		return (NULL);

	prp->pr_pvp = NULL;
	prp->pr_ident = idp;

	p = strrchr(idp->di_name, ':');
	assert(p != NULL);
	prp->pr_name = p + 1;

	prp->pr_nargs = nargs;
	prp->pr_nargv = dt_alloc(dtp, sizeof (dt_node_t *) * nargc);
	prp->pr_nargc = nargc;
	prp->pr_xargs = xargs;
	prp->pr_xargv = dt_alloc(dtp, sizeof (dt_node_t *) * xargc);
	prp->pr_xargc = xargc;
	prp->pr_mapping = dt_alloc(dtp, sizeof (uint8_t) * xargc);
	prp->pr_inst = NULL;
	prp->pr_argv = dt_alloc(dtp, sizeof (dtrace_typeinfo_t) * xargc);
	prp->pr_argc = xargc;

	if ((prp->pr_nargc != 0 && prp->pr_nargv == NULL) ||
	    (prp->pr_xargc != 0 && prp->pr_xargv == NULL) ||
	    (prp->pr_xargc != 0 && prp->pr_mapping == NULL) ||
	    (prp->pr_argc != 0 && prp->pr_argv == NULL)) {
		dt_probe_destroy(prp);
		return (NULL);
	}

	for (i = 0; i < xargc; i++, xargs = xargs->dn_list) {
		if (xargs->dn_string != NULL)
			prp->pr_mapping[i] = dt_probe_argmap(xargs, nargs);
		else
			prp->pr_mapping[i] = i;

		prp->pr_xargv[i] = xargs;

		if ((dmp = dt_module_lookup_by_ctf(dtp,
		    xargs->dn_ctfp)) != NULL)
			prp->pr_argv[i].dtt_object = dmp->dm_name;
		else
			prp->pr_argv[i].dtt_object = NULL;

		prp->pr_argv[i].dtt_ctfp = xargs->dn_ctfp;
		prp->pr_argv[i].dtt_type = xargs->dn_type;
	}

	for (i = 0; i < nargc; i++, nargs = nargs->dn_list)
		prp->pr_nargv[i] = nargs;

	idp->di_data = prp;
	return (prp);
}