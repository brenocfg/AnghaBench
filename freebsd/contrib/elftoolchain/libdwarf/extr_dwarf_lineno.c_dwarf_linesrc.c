#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ ln_fileno; TYPE_1__* ln_li; } ;
struct TYPE_9__ {char* lf_fname; scalar_t__ lf_fullpath; } ;
struct TYPE_8__ {int /*<<< orphan*/  li_lflist; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_LineInfo ;
typedef  TYPE_2__* Dwarf_LineFile ;
typedef  TYPE_3__* Dwarf_Line ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_LINE_FILE_NUM_BAD ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 TYPE_2__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_2__* STAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_next ; 

int
dwarf_linesrc(Dwarf_Line ln, char **ret_linesrc, Dwarf_Error *error)
{
	Dwarf_LineInfo li;
	Dwarf_LineFile lf;
	int i;

	if (ln == NULL || ret_linesrc == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	li = ln->ln_li;
	assert(li != NULL);

	for (i = 1, lf = STAILQ_FIRST(&li->li_lflist);
	     (Dwarf_Unsigned) i < ln->ln_fileno && lf != NULL;
	     i++, lf = STAILQ_NEXT(lf, lf_next))
		;

	if (lf == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_LINE_FILE_NUM_BAD);
		return (DW_DLV_ERROR);
	}

	if (lf->lf_fullpath) {
		*ret_linesrc = (char *) lf->lf_fullpath;
		return (DW_DLV_OK);
	}

	*ret_linesrc = lf->lf_fname;

	return (DW_DLV_OK);
}