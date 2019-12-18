#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  void* uchar_t ;
struct TYPE_33__ {int /*<<< orphan*/  dtt_flags; int /*<<< orphan*/  dtt_type; int /*<<< orphan*/  dtt_ctfp; } ;
typedef  TYPE_1__ dtrace_typeinfo_t ;
struct TYPE_34__ {int /*<<< orphan*/  dts_name; int /*<<< orphan*/  dts_object; } ;
typedef  TYPE_2__ dtrace_syminfo_t ;
struct TYPE_35__ {scalar_t__ dt_errno; int /*<<< orphan*/  dt_gen; int /*<<< orphan*/ * dt_tls; TYPE_6__* dt_externs; TYPE_5__* dt_ddefs; int /*<<< orphan*/ * dt_globals; } ;
typedef  TYPE_3__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dtrace_attribute_t ;
struct TYPE_36__ {char* dn_string; int dn_flags; TYPE_6__* dn_ident; void* dn_kind; } ;
typedef  TYPE_4__ dt_node_t ;
struct TYPE_37__ {int dm_flags; } ;
typedef  TYPE_5__ dt_module_t ;
typedef  int /*<<< orphan*/  dt_idhash_t ;
struct TYPE_38__ {scalar_t__ di_kind; int di_flags; int /*<<< orphan*/  di_attr; int /*<<< orphan*/  di_type; int /*<<< orphan*/  di_ctfp; TYPE_2__* di_data; struct TYPE_38__* di_next; int /*<<< orphan*/  di_name; } ;
typedef  TYPE_6__ dt_ident_t ;
struct TYPE_39__ {int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/ * pcb_locals; int /*<<< orphan*/  pcb_globals; TYPE_3__* pcb_hdl; } ;
typedef  int /*<<< orphan*/  GElf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int B_TRUE ; 
 char const* DTRACE_OBJ_EXEC ; 
 char* DTRACE_OBJ_KMODS ; 
 char* DTRACE_OBJ_UMODS ; 
 int DT_DM_KERNEL ; 
 int DT_DM_PRIMARY ; 
 int /*<<< orphan*/  DT_DYN_CTFP (TYPE_3__*) ; 
 int /*<<< orphan*/  DT_DYN_TYPE (TYPE_3__*) ; 
 scalar_t__ DT_IDENT_AGG ; 
 scalar_t__ DT_IDENT_ARRAY ; 
 int /*<<< orphan*/  DT_IDENT_SYMBOL ; 
 scalar_t__ DT_IDFLG_LOCAL ; 
 int DT_IDFLG_PRIM ; 
 scalar_t__ DT_IDFLG_TLS ; 
 int DT_IDFLG_USER ; 
 int DT_IDFLG_WRITE ; 
 int DT_NF_LVALUE ; 
 int DT_NF_USERLAND ; 
 int DT_NF_WRITABLE ; 
 void* DT_NODE_AGG ; 
 void* DT_NODE_SYM ; 
 void* DT_NODE_VAR ; 
 int /*<<< orphan*/  D_IDENT_BADREF ; 
 int /*<<< orphan*/  D_IDENT_UNDEF ; 
 int /*<<< orphan*/  D_ID_OFLOW ; 
 int /*<<< orphan*/  D_SYM_BADREF ; 
 int /*<<< orphan*/  D_SYM_MODEL ; 
 int /*<<< orphan*/  D_SYM_NOTYPES ; 
 scalar_t__ EDT_DATAMODEL ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  EDT_NOVAR ; 
 int /*<<< orphan*/  _dtrace_defattr ; 
 int /*<<< orphan*/  _dtrace_symattr ; 
 int /*<<< orphan*/  bcopy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  dt_dprintf (char*,char const*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dt_ident_cook (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* dt_ident_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* dt_idhash_insert (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* dt_idhash_lookup (int /*<<< orphan*/ *,char*) ; 
 char* dt_idhash_name (int /*<<< orphan*/ *) ; 
 int dt_idhash_nextid (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  dt_idkind_name (scalar_t__) ; 
 int /*<<< orphan*/  dt_idops_assc ; 
 int /*<<< orphan*/  dt_idops_thaw ; 
 TYPE_6__* dt_idstack_lookup (int /*<<< orphan*/ *,char*) ; 
 TYPE_5__* dt_module_lookup_by_name (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_module_modelname (TYPE_5__*) ; 
 int /*<<< orphan*/  dt_node_attr_assign (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_node_type_assign (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 
 char const* dtrace_errmsg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (TYPE_3__*) ; 
 scalar_t__ dtrace_lookup_by_name (TYPE_3__*,char const*,char*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ dtrace_symbol_type (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,char const* const,char const*,...) ; 
 TYPE_7__* yypcb ; 

__attribute__((used)) static void
dt_xcook_ident(dt_node_t *dnp, dt_idhash_t *dhp, uint_t idkind, int create)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	const char *sname = dt_idhash_name(dhp);
	int uref = 0;

	dtrace_attribute_t attr = _dtrace_defattr;
	dt_ident_t *idp;
	dtrace_syminfo_t dts;
	GElf_Sym sym;

	const char *scope, *mark;
	uchar_t dnkind;
	char *name;

	/*
	 * Look for scoping marks in the identifier.  If one is found, set our
	 * scope to either DTRACE_OBJ_KMODS or UMODS or to the first part of
	 * the string that specifies the scope using an explicit module name.
	 * If two marks in a row are found, set 'uref' (user symbol reference).
	 * Otherwise we set scope to DTRACE_OBJ_EXEC, indicating that normal
	 * scope is desired and we should search the specified idhash.
	 */
	if ((name = strrchr(dnp->dn_string, '`')) != NULL) {
		if (name > dnp->dn_string && name[-1] == '`') {
			uref++;
			name[-1] = '\0';
		}

		if (name == dnp->dn_string + uref)
			scope = uref ? DTRACE_OBJ_UMODS : DTRACE_OBJ_KMODS;
		else
			scope = dnp->dn_string;

		*name++ = '\0'; /* leave name pointing after scoping mark */
		dnkind = DT_NODE_VAR;

	} else if (idkind == DT_IDENT_AGG) {
		scope = DTRACE_OBJ_EXEC;
		name = dnp->dn_string + 1;
		dnkind = DT_NODE_AGG;
	} else {
		scope = DTRACE_OBJ_EXEC;
		name = dnp->dn_string;
		dnkind = DT_NODE_VAR;
	}

	/*
	 * If create is set to false, and we fail our idhash lookup, preset
	 * the errno code to EDT_NOVAR for our final error message below.
	 * If we end up calling dtrace_lookup_by_name(), it will reset the
	 * errno appropriately and that error will be reported instead.
	 */
	(void) dt_set_errno(dtp, EDT_NOVAR);
	mark = uref ? "``" : "`";

	if (scope == DTRACE_OBJ_EXEC && (
	    (dhp != dtp->dt_globals &&
	    (idp = dt_idhash_lookup(dhp, name)) != NULL) ||
	    (dhp == dtp->dt_globals &&
	    (idp = dt_idstack_lookup(&yypcb->pcb_globals, name)) != NULL))) {
		/*
		 * Check that we are referencing the ident in the manner that
		 * matches its type if this is a global lookup.  In the TLS or
		 * local case, we don't know how the ident will be used until
		 * the time operator -> is seen; more parsing is needed.
		 */
		if (idp->di_kind != idkind && dhp == dtp->dt_globals) {
			xyerror(D_IDENT_BADREF, "%s '%s' may not be referenced "
			    "as %s\n", dt_idkind_name(idp->di_kind),
			    idp->di_name, dt_idkind_name(idkind));
		}

		/*
		 * Arrays and aggregations are not cooked individually. They
		 * have dynamic types and must be referenced using operator [].
		 * This is handled explicitly by the code for DT_TOK_LBRAC.
		 */
		if (idp->di_kind != DT_IDENT_ARRAY &&
		    idp->di_kind != DT_IDENT_AGG)
			attr = dt_ident_cook(dnp, idp, NULL);
		else {
			dt_node_type_assign(dnp,
			    DT_DYN_CTFP(dtp), DT_DYN_TYPE(dtp), B_FALSE);
			attr = idp->di_attr;
		}

		free(dnp->dn_string);
		dnp->dn_string = NULL;
		dnp->dn_kind = dnkind;
		dnp->dn_ident = idp;
		dnp->dn_flags |= DT_NF_LVALUE;

		if (idp->di_flags & DT_IDFLG_WRITE)
			dnp->dn_flags |= DT_NF_WRITABLE;

		dt_node_attr_assign(dnp, attr);

	} else if (dhp == dtp->dt_globals && scope != DTRACE_OBJ_EXEC &&
	    dtrace_lookup_by_name(dtp, scope, name, &sym, &dts) == 0) {

		dt_module_t *mp = dt_module_lookup_by_name(dtp, dts.dts_object);
		int umod = (mp->dm_flags & DT_DM_KERNEL) == 0;
		static const char *const kunames[] = { "kernel", "user" };

		dtrace_typeinfo_t dtt;
		dtrace_syminfo_t *sip;

		if (uref ^ umod) {
			xyerror(D_SYM_BADREF, "%s module '%s' symbol '%s' may "
			    "not be referenced as a %s symbol\n", kunames[umod],
			    dts.dts_object, dts.dts_name, kunames[uref]);
		}

		if (dtrace_symbol_type(dtp, &sym, &dts, &dtt) != 0) {
			/*
			 * For now, we special-case EDT_DATAMODEL to clarify
			 * that mixed data models are not currently supported.
			 */
			if (dtp->dt_errno == EDT_DATAMODEL) {
				xyerror(D_SYM_MODEL, "cannot use %s symbol "
				    "%s%s%s in a %s D program\n",
				    dt_module_modelname(mp),
				    dts.dts_object, mark, dts.dts_name,
				    dt_module_modelname(dtp->dt_ddefs));
			}

			xyerror(D_SYM_NOTYPES,
			    "no symbolic type information is available for "
			    "%s%s%s: %s\n", dts.dts_object, mark, dts.dts_name,
			    dtrace_errmsg(dtp, dtrace_errno(dtp)));
		}

		idp = dt_ident_create(name, DT_IDENT_SYMBOL, 0, 0,
		    _dtrace_symattr, 0, &dt_idops_thaw, NULL, dtp->dt_gen);

		if (idp == NULL)
			longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

		if (mp->dm_flags & DT_DM_PRIMARY)
			idp->di_flags |= DT_IDFLG_PRIM;

		idp->di_next = dtp->dt_externs;
		dtp->dt_externs = idp;

		if ((sip = malloc(sizeof (dtrace_syminfo_t))) == NULL)
			longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

		bcopy(&dts, sip, sizeof (dtrace_syminfo_t));
		idp->di_data = sip;
		idp->di_ctfp = dtt.dtt_ctfp;
		idp->di_type = dtt.dtt_type;

		free(dnp->dn_string);
		dnp->dn_string = NULL;
		dnp->dn_kind = DT_NODE_SYM;
		dnp->dn_ident = idp;
		dnp->dn_flags |= DT_NF_LVALUE;

		dt_node_type_assign(dnp, dtt.dtt_ctfp, dtt.dtt_type,
		    dtt.dtt_flags);
		dt_node_attr_assign(dnp, _dtrace_symattr);

		if (uref) {
			idp->di_flags |= DT_IDFLG_USER;
			dnp->dn_flags |= DT_NF_USERLAND;
		}

	} else if (scope == DTRACE_OBJ_EXEC && create == B_TRUE) {
		uint_t flags = DT_IDFLG_WRITE;
		uint_t id;

		if (dt_idhash_nextid(dhp, &id) == -1) {
			xyerror(D_ID_OFLOW, "cannot create %s: limit on number "
			    "of %s variables exceeded\n", name, sname);
		}

		if (dhp == yypcb->pcb_locals)
			flags |= DT_IDFLG_LOCAL;
		else if (dhp == dtp->dt_tls)
			flags |= DT_IDFLG_TLS;

		dt_dprintf("create %s %s variable %s, id=%u\n",
		    sname, dt_idkind_name(idkind), name, id);

		if (idkind == DT_IDENT_ARRAY || idkind == DT_IDENT_AGG) {
			idp = dt_idhash_insert(dhp, name,
			    idkind, flags, id, _dtrace_defattr, 0,
			    &dt_idops_assc, NULL, dtp->dt_gen);
		} else {
			idp = dt_idhash_insert(dhp, name,
			    idkind, flags, id, _dtrace_defattr, 0,
			    &dt_idops_thaw, NULL, dtp->dt_gen);
		}

		if (idp == NULL)
			longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

		/*
		 * Arrays and aggregations are not cooked individually. They
		 * have dynamic types and must be referenced using operator [].
		 * This is handled explicitly by the code for DT_TOK_LBRAC.
		 */
		if (idp->di_kind != DT_IDENT_ARRAY &&
		    idp->di_kind != DT_IDENT_AGG)
			attr = dt_ident_cook(dnp, idp, NULL);
		else {
			dt_node_type_assign(dnp,
			    DT_DYN_CTFP(dtp), DT_DYN_TYPE(dtp), B_FALSE);
			attr = idp->di_attr;
		}

		free(dnp->dn_string);
		dnp->dn_string = NULL;
		dnp->dn_kind = dnkind;
		dnp->dn_ident = idp;
		dnp->dn_flags |= DT_NF_LVALUE | DT_NF_WRITABLE;

		dt_node_attr_assign(dnp, attr);

	} else if (scope != DTRACE_OBJ_EXEC) {
		xyerror(D_IDENT_UNDEF, "failed to resolve %s%s%s: %s\n",
		    dnp->dn_string, mark, name,
		    dtrace_errmsg(dtp, dtrace_errno(dtp)));
	} else {
		xyerror(D_IDENT_UNDEF, "failed to resolve %s: %s\n",
		    dnp->dn_string, dtrace_errmsg(dtp, dtrace_errno(dtp)));
	}
}