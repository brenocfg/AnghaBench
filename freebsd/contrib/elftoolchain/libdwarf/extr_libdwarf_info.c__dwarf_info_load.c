#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct _Dwarf_CU {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  signature; } ;
struct TYPE_13__ {int cu_dwarf_size; int cu_length_size; int cu_version; int cu_abbrev_offset; int cu_abbrev_offset_cur; int cu_pointer_size; int cu_type_offset; scalar_t__ cu_1st_offset; TYPE_1__ cu_type_sig; scalar_t__ cu_next_offset; scalar_t__ cu_length; scalar_t__ cu_offset; scalar_t__ cu_is_info; TYPE_3__* cu_dbg; } ;
struct TYPE_12__ {int dbg_info_loaded; scalar_t__ dbg_info_off; int dbg_types_loaded; scalar_t__ dbg_types_off; scalar_t__ (* read ) (scalar_t__,scalar_t__*,int) ;int /*<<< orphan*/  dbg_tu; int /*<<< orphan*/  dbg_cu; TYPE_2__* dbg_types_sec; TYPE_2__* dbg_info_sec; } ;
struct TYPE_11__ {scalar_t__ ds_size; scalar_t__ ds_data; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_2__ Dwarf_Section ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_3__* Dwarf_Debug ;
typedef  TYPE_4__* Dwarf_CU ;
typedef  scalar_t__ Dwarf_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_CU_LENGTH_ERROR ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int DW_DLE_NO_ENTRY ; 
 int DW_DLE_VERSION_STAMP_ERROR ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  cu_next ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__*,int) ; 
 scalar_t__ stub2 (scalar_t__,scalar_t__*,int) ; 
 int stub3 (scalar_t__,scalar_t__*,int) ; 
 int stub4 (scalar_t__,scalar_t__*,int) ; 
 int stub5 (scalar_t__,scalar_t__*,int) ; 
 int stub6 (scalar_t__,scalar_t__*,int) ; 

int
_dwarf_info_load(Dwarf_Debug dbg, Dwarf_Bool load_all, Dwarf_Bool is_info,
    Dwarf_Error *error)
{
	Dwarf_CU cu;
	Dwarf_Section *ds;
	int dwarf_size, ret;
	uint64_t length;
	uint64_t next_offset;
	uint64_t offset;

	ret = DW_DLE_NONE;

	if (is_info) {
		if (dbg->dbg_info_loaded)
			return (ret);
		offset = dbg->dbg_info_off;
		ds = dbg->dbg_info_sec;
		if (ds == NULL)
			return (DW_DLE_NO_ENTRY);
	} else {
		if (dbg->dbg_types_loaded)
			return (ret);
		offset = dbg->dbg_types_off;
		ds = dbg->dbg_types_sec;
		if (ds == NULL)
			return (DW_DLE_NO_ENTRY);
	}

	while (offset < ds->ds_size) {
		if ((cu = calloc(1, sizeof(struct _Dwarf_CU))) == NULL) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}

		cu->cu_dbg = dbg;
		cu->cu_is_info = is_info;
		cu->cu_offset = offset;

		length = dbg->read(ds->ds_data, &offset, 4);
		if (length == 0xffffffff) {
			length = dbg->read(ds->ds_data, &offset, 8);
			dwarf_size = 8;
		} else
			dwarf_size = 4;
		cu->cu_dwarf_size = dwarf_size;

		/*
		 * Check if there is enough ELF data for this CU. This assumes
		 * that libelf gives us the entire section in one Elf_Data
		 * object.
		 */
		if (length > ds->ds_size - offset) {
			free(cu);
			DWARF_SET_ERROR(dbg, error, DW_DLE_CU_LENGTH_ERROR);
			return (DW_DLE_CU_LENGTH_ERROR);
		}

		/* Compute the offset to the next compilation unit: */
		next_offset = offset + length;
		if (is_info)
			dbg->dbg_info_off = next_offset;
		else
			dbg->dbg_types_off = next_offset;

		/* Initialise the compilation unit. */
		cu->cu_length		 = length;
		cu->cu_length_size	 = (dwarf_size == 4 ? 4 : 12);
		cu->cu_version		 = dbg->read(ds->ds_data, &offset, 2);
		cu->cu_abbrev_offset	 = dbg->read(ds->ds_data, &offset,
		    dwarf_size);
		cu->cu_abbrev_offset_cur = cu->cu_abbrev_offset;
		cu->cu_pointer_size	 = dbg->read(ds->ds_data, &offset, 1);
		cu->cu_next_offset	 = next_offset;

		/* .debug_types extra fields. */
		if (!is_info) {
			memcpy(cu->cu_type_sig.signature,
			    (char *) ds->ds_data + offset, 8);
			offset += 8;
			cu->cu_type_offset = dbg->read(ds->ds_data, &offset,
			    dwarf_size);
		}

		/* Add the compilation unit to the list. */
		if (is_info)
			STAILQ_INSERT_TAIL(&dbg->dbg_cu, cu, cu_next);
		else
			STAILQ_INSERT_TAIL(&dbg->dbg_tu, cu, cu_next);

		if (cu->cu_version < 2 || cu->cu_version > 4) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_VERSION_STAMP_ERROR);
			ret = DW_DLE_VERSION_STAMP_ERROR;
			break;
		}

		cu->cu_1st_offset = offset;

		offset = next_offset;

		if (!load_all)
			break;
	}

	if (is_info) {
		if ((Dwarf_Unsigned) dbg->dbg_info_off >= ds->ds_size)
			dbg->dbg_info_loaded = 1;
	} else {
		if ((Dwarf_Unsigned) dbg->dbg_types_off >= ds->ds_size)
			dbg->dbg_types_loaded = 1;
	}

	return (ret);
}