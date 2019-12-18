#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  n ;
struct TYPE_26__ {scalar_t__ dtt_type; int /*<<< orphan*/ * dtt_ctfp; int /*<<< orphan*/  dtt_object; scalar_t__ dtt_flags; } ;
typedef  TYPE_3__ dtrace_typeinfo_t ;
struct TYPE_27__ {TYPE_5__* dt_ddefs; int /*<<< orphan*/  dt_ctferr; TYPE_5__* dt_cdefs; } ;
typedef  TYPE_4__ dtrace_hdl_t ;
struct TYPE_28__ {int /*<<< orphan*/ * dm_ctfp; int /*<<< orphan*/  dm_name; } ;
typedef  TYPE_5__ dt_module_t ;
struct TYPE_29__ {int dd_attr; scalar_t__ dd_type; scalar_t__ dd_kind; char* dd_name; int /*<<< orphan*/ * dd_ctfp; TYPE_2__* dd_node; struct TYPE_29__* dd_next; } ;
typedef  TYPE_6__ dt_decl_t ;
typedef  scalar_t__ ctf_id_t ;
struct TYPE_30__ {scalar_t__ ctr_contents; int /*<<< orphan*/  ctr_nelems; int /*<<< orphan*/  ctr_index; } ;
typedef  TYPE_7__ ctf_arinfo_t ;
struct TYPE_24__ {scalar_t__ ds_next; } ;
struct TYPE_31__ {TYPE_1__ pcb_dstack; scalar_t__ pcb_idepth; TYPE_4__* pcb_hdl; } ;
struct TYPE_25__ {scalar_t__ dn_kind; scalar_t__ dn_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ADD_NONROOT ; 
 int /*<<< orphan*/  CTF_ADD_ROOT ; 
 scalar_t__ CTF_ERR ; 
 scalar_t__ CTF_K_ARRAY ; 
#define  CTF_K_ENUM 133 
#define  CTF_K_FLOAT 132 
 scalar_t__ CTF_K_FUNCTION ; 
#define  CTF_K_INTEGER 131 
 scalar_t__ CTF_K_POINTER ; 
#define  CTF_K_STRUCT 130 
#define  CTF_K_TYPEDEF 129 
#define  CTF_K_UNION 128 
 scalar_t__ DTT_FL_USER ; 
 int DT_DA_LONG ; 
 int DT_DA_LONGLONG ; 
 int DT_DA_SHORT ; 
 int DT_DA_SIGNED ; 
 int DT_DA_UNSIGNED ; 
 int DT_DA_USER ; 
 int /*<<< orphan*/ * DT_DYN_CTFP (TYPE_4__*) ; 
 scalar_t__ DT_DYN_TYPE (TYPE_4__*) ; 
 int /*<<< orphan*/ * DT_FPTR_CTFP (TYPE_4__*) ; 
 scalar_t__ DT_FPTR_TYPE (TYPE_4__*) ; 
 int /*<<< orphan*/ * DT_FUNC_CTFP (TYPE_4__*) ; 
 scalar_t__ DT_FUNC_TYPE (TYPE_4__*) ; 
 scalar_t__ DT_NODE_TYPE ; 
 int DT_TYPE_NAMELEN ; 
 int /*<<< orphan*/  D_UNKNOWN ; 
 char* alloca (int) ; 
 scalar_t__ ctf_add_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*) ; 
 scalar_t__ ctf_add_forward (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ctf_add_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ctf_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctf_lookup_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ctf_parent_file (int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_update (int /*<<< orphan*/ *) ; 
 TYPE_5__* dt_module_lookup_by_ctf (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int dt_type_lookup (char*,TYPE_3__*) ; 
 char* dt_type_name (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 int dt_type_pointer (TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_errmsg (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (TYPE_4__*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xywarn (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_8__* yypcb ; 

int
dt_decl_type(dt_decl_t *ddp, dtrace_typeinfo_t *tip)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;

	dt_module_t *dmp;
	ctf_arinfo_t r;
	ctf_id_t type;

	char n[DT_TYPE_NAMELEN];
	uint_t flag;
	char *name;
	int rv;

	tip->dtt_flags = 0;

	/*
	 * Based on our current #include depth and decl stack depth, determine
	 * which dynamic CTF module and scope to use when adding any new types.
	 */
	dmp = yypcb->pcb_idepth ? dtp->dt_cdefs : dtp->dt_ddefs;
	flag = yypcb->pcb_dstack.ds_next ? CTF_ADD_NONROOT : CTF_ADD_ROOT;

	if (ddp->dd_attr & DT_DA_USER)
		tip->dtt_flags = DTT_FL_USER;

	/*
	 * If we have already cached a CTF type for this decl, then we just
	 * return the type information for the cached type.
	 */
	if (ddp->dd_ctfp != NULL &&
	    (dmp = dt_module_lookup_by_ctf(dtp, ddp->dd_ctfp)) != NULL) {
		tip->dtt_object = dmp->dm_name;
		tip->dtt_ctfp = ddp->dd_ctfp;
		tip->dtt_type = ddp->dd_type;
		return (0);
	}

	/*
	 * Currently CTF treats all function pointers identically.  We cache a
	 * representative ID of kind CTF_K_FUNCTION and just return that type.
	 * If we want to support full function declarations, dd_next refers to
	 * the declaration of the function return type, and the parameter list
	 * should be parsed and hung off a new pointer inside of this decl.
	 */
	if (ddp->dd_kind == CTF_K_FUNCTION) {
		tip->dtt_object = dtp->dt_ddefs->dm_name;
		tip->dtt_ctfp = DT_FUNC_CTFP(dtp);
		tip->dtt_type = DT_FUNC_TYPE(dtp);
		return (0);
	}

	/*
	 * If the decl is a pointer, resolve the rest of the stack by calling
	 * dt_decl_type() recursively and then compute a pointer to the result.
	 * Similar to the code above, we return a cached id for function ptrs.
	 */
	if (ddp->dd_kind == CTF_K_POINTER) {
		if (ddp->dd_next->dd_kind == CTF_K_FUNCTION) {
			tip->dtt_object = dtp->dt_ddefs->dm_name;
			tip->dtt_ctfp = DT_FPTR_CTFP(dtp);
			tip->dtt_type = DT_FPTR_TYPE(dtp);
			return (0);
		}

		if ((rv = dt_decl_type(ddp->dd_next, tip)) == 0 &&
		    (rv = dt_type_pointer(tip)) != 0) {
			xywarn(D_UNKNOWN, "cannot find type: %s*: %s\n",
			    dt_type_name(tip->dtt_ctfp, tip->dtt_type,
			    n, sizeof (n)), ctf_errmsg(dtp->dt_ctferr));
		}

		return (rv);
	}

	/*
	 * If the decl is an array, we must find the base type and then call
	 * dt_decl_type() recursively and then build an array of the result.
	 * The C and D multi-dimensional array syntax requires that consecutive
	 * array declarations be processed from right-to-left (i.e. top-down
	 * from the perspective of the declaration stack).  For example, an
	 * array declaration such as int x[3][5] is stored on the stack as:
	 *
	 * (bottom) NULL <- ( INT "int" ) <- ( ARR [3] ) <- ( ARR [5] ) (top)
	 *
	 * but means that x is declared to be an array of 3 objects each of
	 * which is an array of 5 integers, or in CTF representation:
	 *
	 * type T1:( content=int, nelems=5 ) type T2:( content=T1, nelems=3 )
	 *
	 * For more details, refer to K&R[5.7] and ISO C 6.5.2.1.  Rather than
	 * overcomplicate the implementation of dt_decl_type(), we push array
	 * declarations down into the stack in dt_decl_array(), above, so that
	 * by the time dt_decl_type() is called, the decl stack looks like:
	 *
	 * (bottom) NULL <- ( INT "int" ) <- ( ARR [5] ) <- ( ARR [3] ) (top)
	 *
	 * which permits a straightforward recursive descent of the decl stack
	 * to build the corresponding CTF type tree in the appropriate order.
	 */
	if (ddp->dd_kind == CTF_K_ARRAY) {
		/*
		 * If the array decl has a parameter list associated with it,
		 * this is an associative array declaration: return <DYN>.
		 */
		if (ddp->dd_node != NULL &&
		    ddp->dd_node->dn_kind == DT_NODE_TYPE) {
			tip->dtt_object = dtp->dt_ddefs->dm_name;
			tip->dtt_ctfp = DT_DYN_CTFP(dtp);
			tip->dtt_type = DT_DYN_TYPE(dtp);
			return (0);
		}

		if ((rv = dt_decl_type(ddp->dd_next, tip)) != 0)
			return (rv);

		/*
		 * If the array base type is not defined in the target
		 * container or its parent, copy the type to the target
		 * container and reset dtt_ctfp and dtt_type to the copy.
		 */
		if (tip->dtt_ctfp != dmp->dm_ctfp &&
		    tip->dtt_ctfp != ctf_parent_file(dmp->dm_ctfp)) {

			tip->dtt_type = ctf_add_type(dmp->dm_ctfp,
			    tip->dtt_ctfp, tip->dtt_type);
			tip->dtt_ctfp = dmp->dm_ctfp;

			if (tip->dtt_type == CTF_ERR ||
			    ctf_update(tip->dtt_ctfp) == CTF_ERR) {
				xywarn(D_UNKNOWN, "failed to copy type: %s\n",
				    ctf_errmsg(ctf_errno(tip->dtt_ctfp)));
				return (-1);
			}
		}

		/*
		 * The array index type is irrelevant in C and D: just set it
		 * to "long" for all array types that we create on-the-fly.
		 */
		r.ctr_contents = tip->dtt_type;
		r.ctr_index = ctf_lookup_by_name(tip->dtt_ctfp, "long");
		r.ctr_nelems = ddp->dd_node ?
		    (uint_t)ddp->dd_node->dn_value : 0;

		tip->dtt_object = dmp->dm_name;
		tip->dtt_ctfp = dmp->dm_ctfp;
		tip->dtt_type = ctf_add_array(dmp->dm_ctfp, CTF_ADD_ROOT, &r);

		if (tip->dtt_type == CTF_ERR ||
		    ctf_update(tip->dtt_ctfp) == CTF_ERR) {
			xywarn(D_UNKNOWN, "failed to create array type: %s\n",
			    ctf_errmsg(ctf_errno(tip->dtt_ctfp)));
			return (-1);
		}

		return (0);
	}

	/*
	 * Allocate space for the type name and enough space for the maximum
	 * additional text ("unsigned long long \0" requires 20 more bytes).
	 */
	name = alloca(ddp->dd_name ? strlen(ddp->dd_name) + 20 : 20);
	name[0] = '\0';

	switch (ddp->dd_kind) {
	case CTF_K_INTEGER:
	case CTF_K_FLOAT:
		if (ddp->dd_attr & DT_DA_SIGNED)
			(void) strcat(name, "signed ");
		if (ddp->dd_attr & DT_DA_UNSIGNED)
			(void) strcat(name, "unsigned ");
		if (ddp->dd_attr & DT_DA_SHORT)
			(void) strcat(name, "short ");
		if (ddp->dd_attr & DT_DA_LONG)
			(void) strcat(name, "long ");
		if (ddp->dd_attr & DT_DA_LONGLONG)
			(void) strcat(name, "long long ");
		if (ddp->dd_attr == 0 && ddp->dd_name == NULL)
			(void) strcat(name, "int");
		break;
	case CTF_K_STRUCT:
		(void) strcpy(name, "struct ");
		break;
	case CTF_K_UNION:
		(void) strcpy(name, "union ");
		break;
	case CTF_K_ENUM:
		(void) strcpy(name, "enum ");
		break;
	case CTF_K_TYPEDEF:
		break;
	default:
		xywarn(D_UNKNOWN, "internal error -- "
		    "bad decl kind %u\n", ddp->dd_kind);
		return (-1);
	}

	/*
	 * Add dd_name unless a short, long, or long long is explicitly
	 * suffixed by int.  We use the C/CTF canonical names for integers.
	 */
	if (ddp->dd_name != NULL && (ddp->dd_kind != CTF_K_INTEGER ||
	    (ddp->dd_attr & (DT_DA_SHORT | DT_DA_LONG | DT_DA_LONGLONG)) == 0))
		(void) strcat(name, ddp->dd_name);

	/*
	 * Lookup the type.  If we find it, we're done.  Otherwise create a
	 * forward tag for the type if it is a struct, union, or enum.  If
	 * we can't find it and we can't create a tag, return failure.
	 */
	if ((rv = dt_type_lookup(name, tip)) == 0)
		return (rv);

	switch (ddp->dd_kind) {
	case CTF_K_STRUCT:
	case CTF_K_UNION:
	case CTF_K_ENUM:
		type = ctf_add_forward(dmp->dm_ctfp, flag,
		    ddp->dd_name, ddp->dd_kind);
		break;
	default:
		xywarn(D_UNKNOWN, "failed to resolve type %s: %s\n", name,
		    dtrace_errmsg(dtp, dtrace_errno(dtp)));
		return (rv);
	}

	if (type == CTF_ERR || ctf_update(dmp->dm_ctfp) == CTF_ERR) {
		xywarn(D_UNKNOWN, "failed to add forward tag for %s: %s\n",
		    name, ctf_errmsg(ctf_errno(dmp->dm_ctfp)));
		return (-1);
	}

	ddp->dd_ctfp = dmp->dm_ctfp;
	ddp->dd_type = type;

	tip->dtt_object = dmp->dm_name;
	tip->dtt_ctfp = dmp->dm_ctfp;
	tip->dtt_type = type;

	return (0);
}