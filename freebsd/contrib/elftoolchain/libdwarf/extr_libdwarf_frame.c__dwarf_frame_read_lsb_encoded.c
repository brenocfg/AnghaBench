#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_7__ {int cie_addrsize; } ;
struct TYPE_6__ {scalar_t__ (* read ) (int*,scalar_t__*,int) ;} ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;
typedef  TYPE_2__* Dwarf_Cie ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_FRAME_AUGMENTATION_UNKNOWN ; 
 int DW_DLE_NONE ; 
#define  DW_EH_PE_absptr 136 
 int DW_EH_PE_omit ; 
 int DW_EH_PE_pcrel ; 
#define  DW_EH_PE_sdata2 135 
#define  DW_EH_PE_sdata4 134 
#define  DW_EH_PE_sdata8 133 
#define  DW_EH_PE_sleb128 132 
#define  DW_EH_PE_udata2 131 
#define  DW_EH_PE_udata4 130 
#define  DW_EH_PE_udata8 129 
#define  DW_EH_PE_uleb128 128 
 scalar_t__ _dwarf_read_sleb128 (int*,scalar_t__*) ; 
 scalar_t__ _dwarf_read_uleb128 (int*,scalar_t__*) ; 
 scalar_t__ stub1 (int*,scalar_t__*,int) ; 
 scalar_t__ stub2 (int*,scalar_t__*,int) ; 
 scalar_t__ stub3 (int*,scalar_t__*,int) ; 
 scalar_t__ stub4 (int*,scalar_t__*,int) ; 
 scalar_t__ stub5 (int*,scalar_t__*,int) ; 
 scalar_t__ stub6 (int*,scalar_t__*,int) ; 
 scalar_t__ stub7 (int*,scalar_t__*,int) ; 

__attribute__((used)) static int
_dwarf_frame_read_lsb_encoded(Dwarf_Debug dbg, Dwarf_Cie cie, uint64_t *val,
    uint8_t *data, uint64_t *offsetp, uint8_t encode, Dwarf_Addr pc,
    Dwarf_Error *error)
{
	uint8_t application;

	if (encode == DW_EH_PE_omit)
		return (DW_DLE_NONE);

	application = encode & 0xf0;
	encode &= 0x0f;

	switch (encode) {
	case DW_EH_PE_absptr:
		*val = dbg->read(data, offsetp, cie->cie_addrsize);
		break;
	case DW_EH_PE_uleb128:
		*val = _dwarf_read_uleb128(data, offsetp);
		break;
	case DW_EH_PE_udata2:
		*val = dbg->read(data, offsetp, 2);
		break;
	case DW_EH_PE_udata4:
		*val = dbg->read(data, offsetp, 4);
		break;
	case DW_EH_PE_udata8:
		*val = dbg->read(data, offsetp, 8);
		break;
	case DW_EH_PE_sleb128:
		*val = _dwarf_read_sleb128(data, offsetp);
		break;
	case DW_EH_PE_sdata2:
		*val = (int16_t) dbg->read(data, offsetp, 2);
		break;
	case DW_EH_PE_sdata4:
		*val = (int32_t) dbg->read(data, offsetp, 4);
		break;
	case DW_EH_PE_sdata8:
		*val = dbg->read(data, offsetp, 8);
		break;
	default:
		DWARF_SET_ERROR(dbg, error, DW_DLE_FRAME_AUGMENTATION_UNKNOWN);
		return (DW_DLE_FRAME_AUGMENTATION_UNKNOWN);
	}

	if (application == DW_EH_PE_pcrel) {
		/*
		 * Value is relative to .eh_frame section virtual addr.
		 */
		switch (encode) {
		case DW_EH_PE_uleb128:
		case DW_EH_PE_udata2:
		case DW_EH_PE_udata4:
		case DW_EH_PE_udata8:
			*val += pc;
			break;
		case DW_EH_PE_sleb128:
		case DW_EH_PE_sdata2:
		case DW_EH_PE_sdata4:
		case DW_EH_PE_sdata8:
			*val = pc + (int64_t) *val;
			break;
		default:
			/* DW_EH_PE_absptr is absolute value. */
			break;
		}
	}

	/* XXX Applications other than DW_EH_PE_pcrel are not handled. */

	return (DW_DLE_NONE);
}