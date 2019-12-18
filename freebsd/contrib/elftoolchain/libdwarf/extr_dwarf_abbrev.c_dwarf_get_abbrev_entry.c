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
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {scalar_t__ ab_atnum; int /*<<< orphan*/  ab_attrdef; } ;
struct TYPE_7__ {int ad_form; int /*<<< orphan*/  ad_offset; int /*<<< orphan*/  ad_attrib; } ;
typedef  int Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_AttrDef ;
typedef  TYPE_2__* Dwarf_Abbrev ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* STAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad_next ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_abbrev_entry(Dwarf_Abbrev abbrev, Dwarf_Signed ndx,
    Dwarf_Half *attr_num, Dwarf_Signed *form, Dwarf_Off *offset,
    Dwarf_Error *error)
{
	Dwarf_AttrDef ad;
	int i;

	if (abbrev == NULL || attr_num == NULL || form == NULL ||
	    offset == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (ndx < 0 || (uint64_t) ndx >= abbrev->ab_atnum) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	ad = STAILQ_FIRST(&abbrev->ab_attrdef);
	for (i = 0; i < ndx && ad != NULL; i++)
		ad = STAILQ_NEXT(ad, ad_next);

	assert(ad != NULL);

	*attr_num = ad->ad_attrib;
	*form = ad->ad_form;
	*offset = ad->ad_offset;

	return (DW_DLV_OK);
}