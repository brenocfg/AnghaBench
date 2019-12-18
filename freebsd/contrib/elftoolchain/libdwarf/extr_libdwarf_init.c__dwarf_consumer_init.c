#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * ds_name; int /*<<< orphan*/  ds_data; int /*<<< orphan*/  ds_size; int /*<<< orphan*/  ds_addr; } ;
struct TYPE_15__ {int dbg_seccnt; int /*<<< orphan*/  dbg_types_sec; int /*<<< orphan*/  dbg_info_sec; TYPE_6__* dbg_section; int /*<<< orphan*/  dbg_offset_size; int /*<<< orphan*/  dbg_pointer_size; int /*<<< orphan*/  decode; int /*<<< orphan*/  write; int /*<<< orphan*/  read; TYPE_1__* dbg_iface; } ;
struct TYPE_14__ {scalar_t__ (* get_byte_order ) (void*) ;int (* get_section_count ) (void*) ;scalar_t__ (* get_section_info ) (void*,int,TYPE_2__*,int*) ;scalar_t__ (* load_section ) (void*,int,int /*<<< orphan*/ *,int*) ;int /*<<< orphan*/  (* get_length_size ) (void*) ;int /*<<< orphan*/  (* get_pointer_size ) (void*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {void* object; TYPE_3__* methods; } ;
typedef  int Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Section ;
typedef  TYPE_2__ Dwarf_Obj_Access_Section ;
typedef  TYPE_3__ Dwarf_Obj_Access_Methods ;
typedef  int Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_4__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_DEBUG_INFO_NULL ; 
 int DW_DLE_MEMORY ; 
 scalar_t__ DW_DLV_OK ; 
 scalar_t__ DW_OBJECT_MSB ; 
 int /*<<< orphan*/  _dwarf_decode_lsb ; 
 int /*<<< orphan*/  _dwarf_decode_msb ; 
 int /*<<< orphan*/  _dwarf_find_next_types_section (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dwarf_find_section (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  _dwarf_frame_params_init (TYPE_4__*) ; 
 int /*<<< orphan*/  _dwarf_read_lsb ; 
 int /*<<< orphan*/  _dwarf_read_msb ; 
 int /*<<< orphan*/  _dwarf_write_lsb ; 
 int /*<<< orphan*/  _dwarf_write_msb ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_6__* calloc (int,int) ; 
 scalar_t__ stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (void*) ; 
 int stub4 (void*) ; 
 scalar_t__ stub5 (void*,int,TYPE_2__*,int*) ; 
 scalar_t__ stub6 (void*,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
_dwarf_consumer_init(Dwarf_Debug dbg, Dwarf_Error *error)
{
	const Dwarf_Obj_Access_Methods *m;
	Dwarf_Obj_Access_Section sec;
	void *obj;
	Dwarf_Unsigned cnt;
	Dwarf_Half i;
	int ret;

	assert(dbg != NULL);
	assert(dbg->dbg_iface != NULL);

	m = dbg->dbg_iface->methods;
	obj = dbg->dbg_iface->object;

	assert(m != NULL);
	assert(obj != NULL);

	if (m->get_byte_order(obj) == DW_OBJECT_MSB) {
		dbg->read = _dwarf_read_msb;
		dbg->write = _dwarf_write_msb;
		dbg->decode = _dwarf_decode_msb;
	} else {
		dbg->read = _dwarf_read_lsb;
		dbg->write = _dwarf_write_lsb;
		dbg->decode = _dwarf_decode_lsb;
	}

	dbg->dbg_pointer_size = m->get_pointer_size(obj);
	dbg->dbg_offset_size = m->get_length_size(obj);

	cnt = m->get_section_count(obj);

	if (cnt == 0) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_DEBUG_INFO_NULL);
		return (DW_DLE_DEBUG_INFO_NULL);
	}

	dbg->dbg_seccnt = cnt;

	if ((dbg->dbg_section = calloc(cnt + 1, sizeof(Dwarf_Section))) ==
	    NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	for (i = 0; i < cnt; i++) {
		if (m->get_section_info(obj, i, &sec, &ret) != DW_DLV_OK) {
			DWARF_SET_ERROR(dbg, error, ret);
			return (ret);
		}

		dbg->dbg_section[i].ds_addr = sec.addr;
		dbg->dbg_section[i].ds_size = sec.size;
		dbg->dbg_section[i].ds_name = sec.name;

		if (m->load_section(obj, i, &dbg->dbg_section[i].ds_data, &ret)
		    != DW_DLV_OK) {
			DWARF_SET_ERROR(dbg, error, ret);
			return (ret);
		}
	}
	dbg->dbg_section[cnt].ds_name = NULL;

	dbg->dbg_info_sec = _dwarf_find_section(dbg, ".debug_info");

	/* Try to find the optional DWARF4 .debug_types section. */
	dbg->dbg_types_sec = _dwarf_find_next_types_section(dbg, NULL);

	/* Initialise call frame API related parameters. */
	_dwarf_frame_params_init(dbg);

	return (DW_DLV_OK);
}