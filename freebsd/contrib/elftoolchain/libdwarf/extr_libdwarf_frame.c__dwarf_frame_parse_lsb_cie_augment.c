#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {char* cie_augment; char* cie_augdata; int /*<<< orphan*/  cie_fde_encode; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;
typedef  TYPE_1__* Dwarf_Cie ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_FRAME_AUGMENTATION_UNKNOWN ; 
 int DW_DLE_NONE ; 
 int _dwarf_frame_read_lsb_encoded (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
_dwarf_frame_parse_lsb_cie_augment(Dwarf_Debug dbg, Dwarf_Cie cie,
    Dwarf_Error *error)
{
	uint8_t *aug_p, *augdata_p;
	uint64_t val, offset;
	uint8_t encode;
	int ret;

	assert(cie->cie_augment != NULL && *cie->cie_augment == 'z');

	/*
	 * Here we're only interested in the presence of augment 'R'
	 * and associated CIE augment data, which describes the
	 * encoding scheme of FDE PC begin and range.
	 */
	aug_p = &cie->cie_augment[1];
	augdata_p = cie->cie_augdata;
	while (*aug_p != '\0') {
		switch (*aug_p) {
		case 'S':
			break;
		case 'L':
			/* Skip one augment in augment data. */
			augdata_p++;
			break;
		case 'P':
			/* Skip two augments in augment data. */
			encode = *augdata_p++;
			offset = 0;
			ret = _dwarf_frame_read_lsb_encoded(dbg, cie, &val,
			    augdata_p, &offset, encode, 0, error);
			if (ret != DW_DLE_NONE)
				return (ret);
			augdata_p += offset;
			break;
		case 'R':
			cie->cie_fde_encode = *augdata_p++;
			break;
		default:
			DWARF_SET_ERROR(dbg, error,
			    DW_DLE_FRAME_AUGMENTATION_UNKNOWN);
			return (DW_DLE_FRAME_AUGMENTATION_UNKNOWN);
		}
		aug_p++;
	}

	return (DW_DLE_NONE);
}