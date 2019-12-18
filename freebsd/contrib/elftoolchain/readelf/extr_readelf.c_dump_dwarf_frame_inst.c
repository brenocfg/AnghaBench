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
typedef  int /*<<< orphan*/  unk_op ;
typedef  char const* uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct readelf {int dummy; } ;
typedef  char const* intmax_t ;
struct TYPE_4__ {int fp_base_op; int fp_extended_op; int fp_offset; int fp_register; } ;
typedef  int Dwarf_Unsigned ;
typedef  int Dwarf_Small ;
typedef  int Dwarf_Signed ;
typedef  TYPE_1__ Dwarf_Frame_Op ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Cie ;
typedef  int Dwarf_Addr ;

/* Variables and functions */
#define  DW_CFA_advance_loc 141 
#define  DW_CFA_advance_loc1 140 
#define  DW_CFA_advance_loc2 139 
#define  DW_CFA_advance_loc4 138 
#define  DW_CFA_def_cfa 137 
#define  DW_CFA_def_cfa_offset 136 
#define  DW_CFA_def_cfa_offset_sf 135 
#define  DW_CFA_def_cfa_register 134 
#define  DW_CFA_def_cfa_sf 133 
#define  DW_CFA_offset 132 
#define  DW_CFA_offset_extended 131 
#define  DW_CFA_offset_extended_sf 130 
#define  DW_CFA_restore 129 
#define  DW_CFA_set_loc 128 
 int /*<<< orphan*/  DW_DLA_FRAME_BLOCK ; 
 scalar_t__ DW_DLV_OK ; 
 int /*<<< orphan*/  dwarf_dealloc (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_expand_frame_instructions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__**,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_get_CFA_name (int,char const**) ; 
 char* dwarf_regname (struct readelf*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_dwarf_frame_inst(struct readelf *re, Dwarf_Cie cie, uint8_t *insts,
    Dwarf_Unsigned len, Dwarf_Unsigned caf, Dwarf_Signed daf, Dwarf_Addr pc,
    Dwarf_Debug dbg)
{
	Dwarf_Frame_Op *oplist;
	Dwarf_Signed opcnt, delta;
	Dwarf_Small op;
	Dwarf_Error de;
	const char *op_str;
	char unk_op[32];
	int i;

	if (dwarf_expand_frame_instructions(cie, insts, len, &oplist,
	    &opcnt, &de) != DW_DLV_OK) {
		warnx("dwarf_expand_frame_instructions failed: %s",
		    dwarf_errmsg(de));
		return;
	}

	for (i = 0; i < opcnt; i++) {
		if (oplist[i].fp_base_op != 0)
			op = oplist[i].fp_base_op << 6;
		else
			op = oplist[i].fp_extended_op;
		if (dwarf_get_CFA_name(op, &op_str) != DW_DLV_OK) {
			snprintf(unk_op, sizeof(unk_op), "[Unknown CFA: %#x]",
			    op);
			op_str = unk_op;
		}
		printf("  %s", op_str);
		switch (op) {
		case DW_CFA_advance_loc:
			delta = oplist[i].fp_offset * caf;
			pc += delta;
			printf(": %ju to %08jx", (uintmax_t) delta,
			    (uintmax_t) pc);
			break;
		case DW_CFA_offset:
		case DW_CFA_offset_extended:
		case DW_CFA_offset_extended_sf:
			delta = oplist[i].fp_offset * daf;
			printf(": r%u (%s) at cfa%+jd", oplist[i].fp_register,
			    dwarf_regname(re, oplist[i].fp_register),
			    (intmax_t) delta);
			break;
		case DW_CFA_restore:
			printf(": r%u (%s)", oplist[i].fp_register,
			    dwarf_regname(re, oplist[i].fp_register));
			break;
		case DW_CFA_set_loc:
			pc = oplist[i].fp_offset;
			printf(": to %08jx", (uintmax_t) pc);
			break;
		case DW_CFA_advance_loc1:
		case DW_CFA_advance_loc2:
		case DW_CFA_advance_loc4:
			pc += oplist[i].fp_offset;
			printf(": %jd to %08jx", (intmax_t) oplist[i].fp_offset,
			    (uintmax_t) pc);
			break;
		case DW_CFA_def_cfa:
			printf(": r%u (%s) ofs %ju", oplist[i].fp_register,
			    dwarf_regname(re, oplist[i].fp_register),
			    (uintmax_t) oplist[i].fp_offset);
			break;
		case DW_CFA_def_cfa_sf:
			printf(": r%u (%s) ofs %jd", oplist[i].fp_register,
			    dwarf_regname(re, oplist[i].fp_register),
			    (intmax_t) (oplist[i].fp_offset * daf));
			break;
		case DW_CFA_def_cfa_register:
			printf(": r%u (%s)", oplist[i].fp_register,
			    dwarf_regname(re, oplist[i].fp_register));
			break;
		case DW_CFA_def_cfa_offset:
			printf(": %ju", (uintmax_t) oplist[i].fp_offset);
			break;
		case DW_CFA_def_cfa_offset_sf:
			printf(": %jd", (intmax_t) (oplist[i].fp_offset * daf));
			break;
		default:
			break;
		}
		putchar('\n');
	}

	dwarf_dealloc(dbg, oplist, DW_DLA_FRAME_BLOCK);
}