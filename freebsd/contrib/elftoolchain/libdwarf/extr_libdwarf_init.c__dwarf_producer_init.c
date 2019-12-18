#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct _Dwarf_LineInfo {int dummy; } ;
struct _Dwarf_ArangeSet {int dummy; } ;
struct TYPE_8__ {int dbg_offset_size; int dbg_pointer_size; int dbgp_flags; TYPE_2__* dbgp_as; TYPE_1__* dbgp_lineinfo; int /*<<< orphan*/  dbgp_fdelist; int /*<<< orphan*/  dbgp_cielist; int /*<<< orphan*/  dbgp_drslist; int /*<<< orphan*/  dbgp_seclist; int /*<<< orphan*/  dbgp_pelist; int /*<<< orphan*/  dbgp_dielist; int /*<<< orphan*/  write_alloc; int /*<<< orphan*/  write; int /*<<< orphan*/  dbgp_isa; } ;
struct TYPE_7__ {int /*<<< orphan*/  as_arlist; } ;
struct TYPE_6__ {int /*<<< orphan*/  li_lnlist; int /*<<< orphan*/  li_lflist; } ;
typedef  int Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_3__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLC_ISA_IA64 ; 
 int DW_DLC_ISA_MIPS ; 
 int DW_DLC_SIZE_32 ; 
 int DW_DLC_SIZE_64 ; 
 int DW_DLC_STREAM_RELOCATIONS ; 
 int DW_DLC_SYMBOLIC_RELOCATIONS ; 
 int DW_DLC_TARGET_BIGENDIAN ; 
 int DW_DLC_TARGET_LITTLEENDIAN ; 
 int DW_DLE_ARGUMENT ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_ISA_IA64 ; 
 int /*<<< orphan*/  DW_ISA_MIPS ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dwarf_write_lsb ; 
 int /*<<< orphan*/  _dwarf_write_lsb_alloc ; 
 int /*<<< orphan*/  _dwarf_write_msb ; 
 int /*<<< orphan*/  _dwarf_write_msb_alloc ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* calloc (int,int) ; 

__attribute__((used)) static int
_dwarf_producer_init(Dwarf_Debug dbg, Dwarf_Unsigned pf, Dwarf_Error *error)
{

	/* Producer only support DWARF2 which has fixed 32bit offset. */
	dbg->dbg_offset_size = 4;

	if (pf & DW_DLC_SIZE_32 && pf & DW_DLC_SIZE_64) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLE_ARGUMENT);
	}

	if ((pf & DW_DLC_SIZE_32) == 0 && (pf & DW_DLC_SIZE_64) == 0)
		pf |= DW_DLC_SIZE_32;

	if (pf & DW_DLC_SIZE_64)
		dbg->dbg_pointer_size = 8;
	else
		dbg->dbg_pointer_size = 4;

	if (pf & DW_DLC_ISA_IA64 && pf & DW_DLC_ISA_MIPS) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLE_ARGUMENT);
	}

	if (pf & DW_DLC_ISA_IA64)
		dbg->dbgp_isa = DW_ISA_IA64;
	else
		dbg->dbgp_isa = DW_ISA_MIPS;

	if (pf & DW_DLC_TARGET_BIGENDIAN && pf & DW_DLC_TARGET_LITTLEENDIAN) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLE_ARGUMENT);
	}

	if ((pf & DW_DLC_TARGET_BIGENDIAN) == 0 &&
	    (pf & DW_DLC_TARGET_LITTLEENDIAN) == 0) {
#if ELFTC_BYTE_ORDER == ELFTC_BYTE_ORDER_BIG_ENDIAN
		pf |= DW_DLC_TARGET_BIGENDIAN;
#else
		pf |= DW_DLC_TARGET_LITTLEENDIAN;
#endif
	}

	if (pf & DW_DLC_TARGET_BIGENDIAN) {
		dbg->write = _dwarf_write_msb;
		dbg->write_alloc = _dwarf_write_msb_alloc;
	} else if (pf & DW_DLC_TARGET_LITTLEENDIAN) {
		dbg->write = _dwarf_write_lsb;
		dbg->write_alloc = _dwarf_write_lsb_alloc;
	} else
		assert(0);

	if (pf & DW_DLC_STREAM_RELOCATIONS &&
	    pf & DW_DLC_SYMBOLIC_RELOCATIONS) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLE_ARGUMENT);
	}

	if ((pf & DW_DLC_STREAM_RELOCATIONS) == 0 &&
	    (pf & DW_DLC_SYMBOLIC_RELOCATIONS) == 0)
		pf |= DW_DLC_STREAM_RELOCATIONS;

	dbg->dbgp_flags = pf;

	STAILQ_INIT(&dbg->dbgp_dielist);
	STAILQ_INIT(&dbg->dbgp_pelist);
	STAILQ_INIT(&dbg->dbgp_seclist);
	STAILQ_INIT(&dbg->dbgp_drslist);
	STAILQ_INIT(&dbg->dbgp_cielist);
	STAILQ_INIT(&dbg->dbgp_fdelist);

	if ((dbg->dbgp_lineinfo = calloc(1, sizeof(struct _Dwarf_LineInfo))) ==
	    NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}
	STAILQ_INIT(&dbg->dbgp_lineinfo->li_lflist);
	STAILQ_INIT(&dbg->dbgp_lineinfo->li_lnlist);

	if ((dbg->dbgp_as = calloc(1, sizeof(struct _Dwarf_ArangeSet))) ==
	    NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}
	STAILQ_INIT(&dbg->dbgp_as->as_arlist);

	return (DW_DLE_NONE);
}