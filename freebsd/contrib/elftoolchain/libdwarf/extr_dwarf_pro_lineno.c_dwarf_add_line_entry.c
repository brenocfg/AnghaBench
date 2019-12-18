#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct _Dwarf_Line {int dummy; } ;
struct TYPE_11__ {scalar_t__ ln_addr; int ln_bblock; int ln_stmt; scalar_t__ ln_endseq; int /*<<< orphan*/  ln_column; void* ln_lineno; void* ln_fileno; scalar_t__ ln_symndx; TYPE_2__* ln_li; } ;
struct TYPE_10__ {int /*<<< orphan*/  li_lnlen; int /*<<< orphan*/  li_lnlist; } ;
struct TYPE_9__ {TYPE_2__* dbgp_lineinfo; } ;
typedef  void* Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  TYPE_2__* Dwarf_LineInfo ;
typedef  TYPE_3__* Dwarf_Line ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  scalar_t__ Dwarf_Bool ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_MEMORY ; 
 void* DW_DLV_NOCOUNT ; 
 void* DW_DLV_OK ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* STAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _Dwarf_Line ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  ln_next ; 

Dwarf_Unsigned
dwarf_add_line_entry(Dwarf_P_Debug dbg, Dwarf_Unsigned file,
    Dwarf_Addr off, Dwarf_Unsigned lineno, Dwarf_Signed column,
    Dwarf_Bool is_stmt, Dwarf_Bool basic_block, Dwarf_Error *error)
{
	Dwarf_LineInfo li;
	Dwarf_Line ln;

	if (dbg == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_NOCOUNT);
	}

	li = dbg->dbgp_lineinfo;

	ln = STAILQ_LAST(&li->li_lnlist, _Dwarf_Line, ln_next);

	if (ln == NULL || ln->ln_addr > off) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_NOCOUNT);
	}

	if ((ln = calloc(1, sizeof(struct _Dwarf_Line))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLV_NOCOUNT);
	}
	ln->ln_li     = li;
	ln->ln_addr   = off;
	ln->ln_symndx = 0;
	ln->ln_fileno = file;
	ln->ln_lineno = lineno;
	ln->ln_column = column;
	ln->ln_bblock = basic_block != 0;
	ln->ln_stmt   = is_stmt != 0;
	ln->ln_endseq = 0;
	STAILQ_INSERT_TAIL(&li->li_lnlist, ln, ln_next);
	li->li_lnlen++;

	return (DW_DLV_OK);
}