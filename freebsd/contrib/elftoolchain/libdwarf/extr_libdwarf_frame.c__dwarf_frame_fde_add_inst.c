#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int dbg_pointer_size; } ;
struct TYPE_5__ {scalar_t__ fde_instcap; int /*<<< orphan*/ * fde_inst; scalar_t__ fde_instlen; TYPE_2__* fde_dbg; } ;
typedef  int Dwarf_Unsigned ;
typedef  int Dwarf_Small ;
typedef  TYPE_1__* Dwarf_P_Fde ;
typedef  TYPE_2__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
#define  DW_CFA_advance_loc 144 
#define  DW_CFA_advance_loc1 143 
#define  DW_CFA_advance_loc2 142 
#define  DW_CFA_advance_loc4 141 
#define  DW_CFA_def_cfa 140 
#define  DW_CFA_def_cfa_offset 139 
#define  DW_CFA_def_cfa_register 138 
 int DW_CFA_nop ; 
#define  DW_CFA_offset 137 
#define  DW_CFA_offset_extended 136 
#define  DW_CFA_register 135 
#define  DW_CFA_remember_state 134 
#define  DW_CFA_restore 133 
#define  DW_CFA_restore_extended 132 
#define  DW_CFA_restore_state 131 
#define  DW_CFA_same_value 130 
#define  DW_CFA_set_loc 129 
#define  DW_CFA_undefined 128 
 int DW_DLE_FRAME_INSTR_EXEC_ERROR ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  RCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ULEB128 (int) ; 
 int /*<<< orphan*/  WRITE_VALUE (int,int) ; 
 scalar_t__ _FDE_INST_INIT_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

int
_dwarf_frame_fde_add_inst(Dwarf_P_Fde fde, Dwarf_Small op, Dwarf_Unsigned val1,
    Dwarf_Unsigned val2, Dwarf_Error *error)
{
	Dwarf_P_Debug dbg;
	uint8_t high2, low6;
	int ret;

#define	ds	fde
#define	ds_data	fde_inst
#define	ds_cap	fde_instcap
#define	ds_size	fde_instlen

	assert(fde != NULL && fde->fde_dbg != NULL);
	dbg = fde->fde_dbg;

	if (fde->fde_inst == NULL) {
		fde->fde_instcap = _FDE_INST_INIT_SIZE;
		fde->fde_instlen = 0;
		if ((fde->fde_inst = malloc((size_t) fde->fde_instcap)) ==
		    NULL) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}
	}
	assert(fde->fde_instcap != 0);

	RCHECK(WRITE_VALUE(op, 1));
	if (op == DW_CFA_nop)
		return (DW_DLE_NONE);

	high2 = op & 0xc0;
	low6 = op & 0x3f;

	if (high2 > 0) {
		switch (high2) {
		case DW_CFA_advance_loc:
		case DW_CFA_restore:
			break;
		case DW_CFA_offset:
			RCHECK(WRITE_ULEB128(val1));
			break;
		default:
			DWARF_SET_ERROR(dbg, error,
			    DW_DLE_FRAME_INSTR_EXEC_ERROR);
			return (DW_DLE_FRAME_INSTR_EXEC_ERROR);
		}
		return (DW_DLE_NONE);
	}

	switch (low6) {
	case DW_CFA_set_loc:
		RCHECK(WRITE_VALUE(val1, dbg->dbg_pointer_size));
		break;
	case DW_CFA_advance_loc1:
		RCHECK(WRITE_VALUE(val1, 1));
		break;
	case DW_CFA_advance_loc2:
		RCHECK(WRITE_VALUE(val1, 2));
		break;
	case DW_CFA_advance_loc4:
		RCHECK(WRITE_VALUE(val1, 4));
		break;
	case DW_CFA_offset_extended:
	case DW_CFA_def_cfa:
	case DW_CFA_register:
		RCHECK(WRITE_ULEB128(val1));
		RCHECK(WRITE_ULEB128(val2));
		break;
	case DW_CFA_restore_extended:
	case DW_CFA_undefined:
	case DW_CFA_same_value:
	case DW_CFA_def_cfa_register:
	case DW_CFA_def_cfa_offset:
		RCHECK(WRITE_ULEB128(val1));
		break;
	case DW_CFA_remember_state:
	case DW_CFA_restore_state:
		break;
	default:
		DWARF_SET_ERROR(dbg, error, DW_DLE_FRAME_INSTR_EXEC_ERROR);
		return (DW_DLE_FRAME_INSTR_EXEC_ERROR);
	}

	return (DW_DLE_NONE);

gen_fail:
	return (ret);

#undef	ds
#undef	ds_data
#undef	ds_cap
#undef	ds_size
}