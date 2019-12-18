#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  n ;
struct TYPE_20__ {struct TYPE_20__* dn_list; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_21__ {int dis_varargs; int dis_optargs; int dis_argc; TYPE_8__* dis_args; scalar_t__ dis_auxinfo; } ;
typedef  TYPE_2__ dt_idsig_t ;
struct TYPE_22__ {int di_flags; scalar_t__ di_kind; int /*<<< orphan*/  di_type; int /*<<< orphan*/  di_ctfp; TYPE_2__* di_data; } ;
typedef  TYPE_3__ dt_ident_t ;
struct TYPE_24__ {struct TYPE_24__* dn_list; } ;
struct TYPE_23__ {int /*<<< orphan*/  pcb_hdl; int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DT_DYN_CTFP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DT_DYN_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ DT_IDENT_AGG ; 
 int DT_IDFLG_DECL ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_KEY_TYPE ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 TYPE_8__* calloc (int,int) ; 
 int /*<<< orphan*/  dt_idcook_sign (TYPE_1__*,TYPE_3__*,int,TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  dt_idkind_name (scalar_t__) ; 
 scalar_t__ dt_node_is_dynamic (TYPE_1__*) ; 
 scalar_t__ dt_node_is_void (TYPE_1__*) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dt_node_type_propagate (TYPE_1__*,TYPE_8__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* yypcb ; 

__attribute__((used)) static void
dt_idcook_assc(dt_node_t *dnp, dt_ident_t *idp, int argc, dt_node_t *args)
{
	if (idp->di_data == NULL) {
		dt_idsig_t *isp = idp->di_data = malloc(sizeof (dt_idsig_t));
		char n[DT_TYPE_NAMELEN];
		int i;

		if (isp == NULL)
			longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

		isp->dis_varargs = -1;
		isp->dis_optargs = -1;
		isp->dis_argc = argc;
		isp->dis_args = NULL;
		isp->dis_auxinfo = 0;

		if (argc != 0 && (isp->dis_args = calloc(argc,
		    sizeof (dt_node_t))) == NULL) {
			idp->di_data = NULL;
			free(isp);
			longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);
		}

		/*
		 * If this identifier has not been explicitly declared earlier,
		 * set the identifier's base type to be our special type <DYN>.
		 * If this ident is an aggregation, it will remain as is.  If
		 * this ident is an associative array, it will be reassigned
		 * based on the result type of the first assignment statement.
		 */
		if (!(idp->di_flags & DT_IDFLG_DECL)) {
			idp->di_ctfp = DT_DYN_CTFP(yypcb->pcb_hdl);
			idp->di_type = DT_DYN_TYPE(yypcb->pcb_hdl);
		}

		for (i = 0; i < argc; i++, args = args->dn_list) {
			if (dt_node_is_dynamic(args) || dt_node_is_void(args)) {
				xyerror(D_KEY_TYPE, "%s expression may not be "
				    "used as %s index: key #%d\n",
				    dt_node_type_name(args, n, sizeof (n)),
				    dt_idkind_name(idp->di_kind), i + 1);
			}

			dt_node_type_propagate(args, &isp->dis_args[i]);
			isp->dis_args[i].dn_list = &isp->dis_args[i + 1];
		}

		if (argc != 0)
			isp->dis_args[argc - 1].dn_list = NULL;

		dt_node_type_assign(dnp, idp->di_ctfp, idp->di_type, B_FALSE);

	} else {
		dt_idcook_sign(dnp, idp, argc, args,
		    idp->di_kind == DT_IDENT_AGG ? "@" : "", "[ ]");
	}
}