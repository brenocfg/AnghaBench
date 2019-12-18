#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  n2 ;
typedef  int /*<<< orphan*/  n1 ;
struct TYPE_11__ {int /*<<< orphan*/ * dn_ctfp; struct TYPE_11__* dn_list; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_12__ {int dis_varargs; int dis_optargs; int dis_argc; TYPE_1__* dis_args; } ;
typedef  TYPE_2__ dt_idsig_t ;
struct TYPE_13__ {scalar_t__ di_kind; int /*<<< orphan*/  di_type; int /*<<< orphan*/  di_ctfp; int /*<<< orphan*/  di_name; TYPE_2__* di_data; } ;
typedef  TYPE_3__ dt_ident_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ DT_IDENT_AGG ; 
 scalar_t__ DT_IDENT_ARRAY ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_PROTO_ARG ; 
 int /*<<< orphan*/  D_PROTO_LEN ; 
 int dt_node_is_argcompat (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,char const*,...) ; 

__attribute__((used)) static void
dt_idcook_sign(dt_node_t *dnp, dt_ident_t *idp,
    int argc, dt_node_t *args, const char *prefix, const char *suffix)
{
	dt_idsig_t *isp = idp->di_data;
	int i, compat, mismatch, arglimit, iskey;

	char n1[DT_TYPE_NAMELEN];
	char n2[DT_TYPE_NAMELEN];

	iskey = idp->di_kind == DT_IDENT_ARRAY || idp->di_kind == DT_IDENT_AGG;

	if (isp->dis_varargs >= 0) {
		mismatch = argc < isp->dis_varargs;
		arglimit = isp->dis_varargs;
	} else if (isp->dis_optargs >= 0) {
		mismatch = (argc < isp->dis_optargs || argc > isp->dis_argc);
		arglimit = argc;
	} else {
		mismatch = argc != isp->dis_argc;
		arglimit = isp->dis_argc;
	}

	if (mismatch) {
		xyerror(D_PROTO_LEN, "%s%s%s prototype mismatch: %d %s%s"
		    "passed, %s%d expected\n", prefix, idp->di_name, suffix,
		    argc, iskey ? "key" : "arg", argc == 1 ? " " : "s ",
		    isp->dis_optargs >= 0 ? "at least " : "",
		    isp->dis_optargs >= 0 ? isp->dis_optargs : arglimit);
	}

	for (i = 0; i < arglimit; i++, args = args->dn_list) {
		if (isp->dis_args[i].dn_ctfp != NULL)
			compat = dt_node_is_argcompat(&isp->dis_args[i], args);
		else
			compat = 1; /* "@" matches any type */

		if (!compat) {
			xyerror(D_PROTO_ARG,
			    "%s%s%s %s #%d is incompatible with "
			    "prototype:\n\tprototype: %s\n\t%9s: %s\n",
			    prefix, idp->di_name, suffix,
			    iskey ? "key" : "argument", i + 1,
			    dt_node_type_name(&isp->dis_args[i], n1,
			    sizeof (n1)),
			    iskey ? "key" : "argument",
			    dt_node_type_name(args, n2, sizeof (n2)));
		}
	}

	dt_node_type_assign(dnp, idp->di_ctfp, idp->di_type, B_FALSE);
}