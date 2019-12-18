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
struct _Dwarf_LineFile {int dummy; } ;
struct TYPE_11__ {void* lf_size; void* lf_mtime; void* lf_dirndx; int /*<<< orphan*/ * lf_fname; } ;
struct TYPE_10__ {void* li_lflen; int /*<<< orphan*/  li_lflist; } ;
struct TYPE_9__ {TYPE_2__* dbgp_lineinfo; } ;
typedef  void* Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  TYPE_2__* Dwarf_LineInfo ;
typedef  TYPE_3__* Dwarf_LineFile ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 
 void* DW_DLE_ARGUMENT ; 
 void* DW_DLE_MEMORY ; 
 void* DW_DLV_NOCOUNT ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  lf_next ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 scalar_t__ strlen (char*) ; 

Dwarf_Unsigned
dwarf_add_file_decl(Dwarf_P_Debug dbg, char *name, Dwarf_Unsigned dirndx,
    Dwarf_Unsigned mtime, Dwarf_Unsigned size, Dwarf_Error *error)
{
	Dwarf_LineInfo li;
	Dwarf_LineFile lf;

	if (dbg == NULL || name == NULL || strlen(name) == 0) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_NOCOUNT);
	}

	li = dbg->dbgp_lineinfo;

	if ((lf = malloc(sizeof(struct _Dwarf_LineFile))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	if ((lf->lf_fname = strdup(name)) == NULL) {
		free(lf);
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}
	lf->lf_dirndx = dirndx;
	lf->lf_mtime = mtime;
	lf->lf_size = size;
	STAILQ_INSERT_TAIL(&li->li_lflist, lf, lf_next);

	return (++li->li_lflen);
}