#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct _Dwarf_Fde {int dummy; } ;
struct TYPE_24__ {int cie_addrsize; char* cie_augment; int /*<<< orphan*/  cie_fde_encode; } ;
struct TYPE_23__ {int (* read ) (int,int*,int) ;} ;
struct TYPE_22__ {int fde_addr; int fde_offset; int fde_length; int fde_cieoff; int fde_initloc; int fde_adrange; int fde_auglen; int fde_augdata; int fde_inst; int fde_instlen; TYPE_5__* fde_cie; TYPE_2__* fde_fs; TYPE_4__* fde_dbg; } ;
struct TYPE_21__ {int /*<<< orphan*/  fs_fdelen; int /*<<< orphan*/  fs_fdelist; } ;
struct TYPE_20__ {int ds_data; int ds_size; int ds_addr; } ;
typedef  int Dwarf_Unsigned ;
typedef  TYPE_1__ Dwarf_Section ;
typedef  TYPE_2__* Dwarf_FrameSec ;
typedef  TYPE_3__* Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_4__* Dwarf_Debug ;
typedef  TYPE_5__* Dwarf_Cie ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_DEBUG_FRAME_LENGTH_BAD ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int DW_DLE_NO_CIE_FOR_FDE ; 
 scalar_t__ DW_DLE_NO_ENTRY ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int _dwarf_frame_add_cie (TYPE_4__*,TYPE_2__*,TYPE_1__*,int*,TYPE_5__**,int /*<<< orphan*/ *) ; 
 scalar_t__ _dwarf_frame_find_cie (TYPE_2__*,int,TYPE_5__**) ; 
 int _dwarf_frame_read_lsb_encoded (TYPE_4__*,TYPE_5__*,int*,int,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int _dwarf_read_uleb128 (int,int*) ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  fde_next ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int stub1 (int,int*,int) ; 
 int stub2 (int,int*,int) ; 
 int stub3 (int,int*,int) ; 
 int stub4 (int,int*,int) ; 
 int stub5 (int,int*,int) ; 
 int stub6 (int,int*,int) ; 

__attribute__((used)) static int
_dwarf_frame_add_fde(Dwarf_Debug dbg, Dwarf_FrameSec fs, Dwarf_Section *ds,
    Dwarf_Unsigned *off, int eh_frame, Dwarf_Error *error)
{
	Dwarf_Cie cie;
	Dwarf_Fde fde;
	Dwarf_Unsigned cieoff;
	uint64_t length, val;
	int dwarf_size, ret;

	if ((fde = calloc(1, sizeof(struct _Dwarf_Fde))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}
	STAILQ_INSERT_TAIL(&fs->fs_fdelist, fde, fde_next);

	fde->fde_dbg = dbg;
	fde->fde_fs = fs;
	fde->fde_addr = ds->ds_data + *off;
	fde->fde_offset = *off;

	length = dbg->read(ds->ds_data, off, 4);
	if (length == 0xffffffff) {
		dwarf_size = 8;
		length = dbg->read(ds->ds_data, off, 8);
	} else
		dwarf_size = 4;

	if (length > ds->ds_size - *off) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_DEBUG_FRAME_LENGTH_BAD);
		return (DW_DLE_DEBUG_FRAME_LENGTH_BAD);
	}

	fde->fde_length = length;

	if (eh_frame) {
		fde->fde_cieoff = dbg->read(ds->ds_data, off, 4);
		cieoff = *off - (4 + fde->fde_cieoff);
		/* This delta should never be 0. */
		if (cieoff == fde->fde_offset) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_NO_CIE_FOR_FDE);
			return (DW_DLE_NO_CIE_FOR_FDE);
		}
	} else {
		fde->fde_cieoff = dbg->read(ds->ds_data, off, dwarf_size);
		cieoff = fde->fde_cieoff;
	}

	if (_dwarf_frame_find_cie(fs, cieoff, &cie) ==
	    DW_DLE_NO_ENTRY) {
		ret = _dwarf_frame_add_cie(dbg, fs, ds, &cieoff, &cie,
		    error);
		if (ret != DW_DLE_NONE)
			return (ret);
	}
	fde->fde_cie = cie;
	if (eh_frame) {
		/*
		 * The FDE PC start/range for .eh_frame is encoded according
		 * to the LSB spec's extension to DWARF2.
		 */
		ret = _dwarf_frame_read_lsb_encoded(dbg, cie, &val,
		    ds->ds_data, off, cie->cie_fde_encode, ds->ds_addr + *off,
		    error);
		if (ret != DW_DLE_NONE)
			return (ret);
		fde->fde_initloc = val;
		/*
		 * FDE PC range should not be relative value to anything.
		 * So pass 0 for pc value.
		 */
		ret = _dwarf_frame_read_lsb_encoded(dbg, cie, &val,
		    ds->ds_data, off, cie->cie_fde_encode, 0, error);
		if (ret != DW_DLE_NONE)
			return (ret);
		fde->fde_adrange = val;
	} else {
		fde->fde_initloc = dbg->read(ds->ds_data, off,
		    cie->cie_addrsize);
		fde->fde_adrange = dbg->read(ds->ds_data, off,
		    cie->cie_addrsize);
	}

	/* Optional FDE augmentation data for .eh_frame section. (ignored) */
	if (eh_frame && *cie->cie_augment == 'z') {
		fde->fde_auglen = _dwarf_read_uleb128(ds->ds_data, off);
		fde->fde_augdata = ds->ds_data + *off;
		*off += fde->fde_auglen;
	}

	fde->fde_inst = ds->ds_data + *off;
	if (dwarf_size == 4)
		fde->fde_instlen = fde->fde_offset + 4 + length - *off;
	else
		fde->fde_instlen = fde->fde_offset + 12 + length - *off;

	*off += fde->fde_instlen;

#ifdef FRAME_DEBUG
	printf("fde:");
	if (eh_frame)
		printf("(eh_frame)");
	putchar('\n');
	printf("\tfde_offset=%ju fde_length=%ju fde_cieoff=%ju"
	    " fde_instlen=%ju off=%ju\n", fde->fde_offset, fde->fde_length,
	    fde->fde_cieoff, fde->fde_instlen, *off);
#endif

	fs->fs_fdelen++;

	return (DW_DLE_NONE);
}