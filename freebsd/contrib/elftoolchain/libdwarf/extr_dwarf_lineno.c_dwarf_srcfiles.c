#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_1__* u; } ;
struct TYPE_18__ {TYPE_2__* cu_lineinfo; } ;
struct TYPE_17__ {TYPE_5__* die_cu; int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_16__ {char* lf_fullpath; char* lf_fname; } ;
struct TYPE_15__ {char** li_lfnarray; int /*<<< orphan*/  li_lflist; scalar_t__ li_lflen; } ;
struct TYPE_14__ {int /*<<< orphan*/  u64; } ;
typedef  int Dwarf_Signed ;
typedef  TYPE_2__* Dwarf_LineInfo ;
typedef  TYPE_3__* Dwarf_LineFile ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_4__* Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_5__* Dwarf_CU ;
typedef  TYPE_6__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_AT_stmt_list ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_MEMORY ; 
 scalar_t__ DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 TYPE_3__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_3__* STAILQ_NEXT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* _dwarf_attr_find (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _dwarf_lineno_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lf_next ; 
 char** malloc (int) ; 

int
dwarf_srcfiles(Dwarf_Die die, char ***srcfiles, Dwarf_Signed *srccount,
    Dwarf_Error *error)
{
	Dwarf_LineInfo li;
	Dwarf_LineFile lf;
	Dwarf_Debug dbg;
	Dwarf_CU cu;
	Dwarf_Attribute at; 
	int i;

	dbg = die != NULL ? die->die_dbg : NULL;

	if (die == NULL || srcfiles == NULL || srccount == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if ((at = _dwarf_attr_find(die, DW_AT_stmt_list)) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	cu = die->die_cu;
	if (cu->cu_lineinfo == NULL) {
		if (_dwarf_lineno_init(die, at->u[0].u64, error) !=
		    DW_DLE_NONE)
			return (DW_DLV_ERROR);
	}
	if (cu->cu_lineinfo == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	li = cu->cu_lineinfo;
	*srccount = (Dwarf_Signed) li->li_lflen;

	if (*srccount == 0) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	if (li->li_lfnarray != NULL) {
		*srcfiles = li->li_lfnarray;
		return (DW_DLV_OK);
	}

	if ((li->li_lfnarray = malloc(*srccount * sizeof(char *))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLV_ERROR);
	}

	for (i = 0, lf = STAILQ_FIRST(&li->li_lflist);
	     i < *srccount && lf != NULL; i++, lf = STAILQ_NEXT(lf, lf_next)) {
		if (lf->lf_fullpath)
			li->li_lfnarray[i] = lf->lf_fullpath;
		else
			li->li_lfnarray[i] = lf->lf_fname;
	}

	*srcfiles = li->li_lfnarray;

	return (DW_DLV_OK);
}