#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cie_instlen; int /*<<< orphan*/  cie_initinst; int /*<<< orphan*/  cie_ra; int /*<<< orphan*/  cie_daf; int /*<<< orphan*/  cie_caf; scalar_t__ cie_augment; int /*<<< orphan*/  cie_version; int /*<<< orphan*/  cie_length; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Small ;
typedef  int /*<<< orphan*/  Dwarf_Ptr ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Cie ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 

int
dwarf_get_cie_info(Dwarf_Cie cie, Dwarf_Unsigned *bytes_in_cie,
    Dwarf_Small *version, char **augmenter, Dwarf_Unsigned *caf,
    Dwarf_Unsigned *daf, Dwarf_Half *ra, Dwarf_Ptr *initinst,
    Dwarf_Unsigned *inst_len, Dwarf_Error *error)
{

	if (cie == NULL || bytes_in_cie == NULL || version == NULL ||
	    augmenter == NULL || caf == NULL || daf == NULL || ra == NULL ||
	    initinst == NULL || inst_len == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	*bytes_in_cie = cie->cie_length;
	*version = cie->cie_version;
	*augmenter = (char *) cie->cie_augment;
	*caf = cie->cie_caf;
	*daf = cie->cie_daf;
	*ra = cie->cie_ra;
	*initinst = cie->cie_initinst;
	*inst_len = cie->cie_instlen;

	return (DW_DLV_OK);
}