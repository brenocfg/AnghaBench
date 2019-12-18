#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dmd_type; int /*<<< orphan*/ * dmd_macro; int /*<<< orphan*/  dmd_fileindex; int /*<<< orphan*/  dmd_lineno; scalar_t__ dmd_offset; } ;
struct TYPE_7__ {size_t dbgp_mdcnt; TYPE_2__* dbgp_mdlist; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  TYPE_2__ Dwarf_Macro_Details ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_MEMORY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/ * malloc (int) ; 
 TYPE_2__* realloc (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
_dwarf_add_macro(Dwarf_P_Debug dbg, int type, Dwarf_Unsigned lineno,
    Dwarf_Signed fileindex, char *str1, char *str2, Dwarf_Error *error)
{
	Dwarf_Macro_Details *md;
	int len;

	dbg->dbgp_mdlist = realloc(dbg->dbgp_mdlist,
	    (size_t) dbg->dbgp_mdcnt + 1);
	if (dbg->dbgp_mdlist == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLV_ERROR);
	}

	md = &dbg->dbgp_mdlist[dbg->dbgp_mdcnt];
	dbg->dbgp_mdcnt++;

	md->dmd_offset = 0;
	md->dmd_type = type;
	md->dmd_lineno = lineno;
	md->dmd_fileindex = fileindex;
	md->dmd_macro = NULL;

	if (str1 == NULL)
		return (DW_DLV_OK);
	else if (str2 == NULL) {
		if ((md->dmd_macro = strdup(str1)) == NULL) {
			dbg->dbgp_mdcnt--;
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLV_ERROR);
		}
		return (DW_DLV_OK);
	} else {
		len = strlen(str1) + strlen(str2) + 2;
		if ((md->dmd_macro = malloc(len)) == NULL) {
			dbg->dbgp_mdcnt--;
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLV_ERROR);
		}
		snprintf(md->dmd_macro, len, "%s %s", str1, str2);
		return (DW_DLV_OK);
	}
}