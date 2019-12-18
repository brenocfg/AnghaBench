#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* die_cu; int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_9__ {int cu_version; } ;
struct TYPE_8__ {int at_attrib; int /*<<< orphan*/ * at_ld; TYPE_5__* at_die; TYPE_1__* u; int /*<<< orphan*/  at_form; } ;
struct TYPE_7__ {int /*<<< orphan*/  u64; } ;
typedef  int Dwarf_Signed ;
typedef  int /*<<< orphan*/ **** Dwarf_Locdesc ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_2__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
#define  DW_AT_data_member_location 144 
#define  DW_AT_frame_base 143 
#define  DW_AT_location 142 
#define  DW_AT_return_addr 141 
#define  DW_AT_segment 140 
#define  DW_AT_static_link 139 
#define  DW_AT_string_length 138 
#define  DW_AT_use_location 137 
#define  DW_AT_vtable_elem_location 136 
 int DW_DLE_ARGUMENT ; 
 int DW_DLE_ATTR_FORM_BAD ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
#define  DW_FORM_block 135 
#define  DW_FORM_block1 134 
#define  DW_FORM_block2 133 
#define  DW_FORM_block4 132 
#define  DW_FORM_data4 131 
#define  DW_FORM_data8 130 
#define  DW_FORM_exprloc 129 
#define  DW_FORM_sec_offset 128 
 int _dwarf_loc_add (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int _dwarf_loclist_find (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *******,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* calloc (int,int) ; 
 int copy_locdesc (int /*<<< orphan*/ *,int /*<<< orphan*/ *****,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ******) ; 

int
dwarf_loclist_n(Dwarf_Attribute at, Dwarf_Locdesc ***llbuf,
    Dwarf_Signed *listlen, Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	int ret;

	dbg = at != NULL ? at->at_die->die_dbg : NULL;

	if (at == NULL || llbuf == NULL || listlen == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	switch (at->at_attrib) {
	case DW_AT_location:
	case DW_AT_string_length:
	case DW_AT_return_addr:
	case DW_AT_data_member_location:
	case DW_AT_frame_base:
	case DW_AT_segment:
	case DW_AT_static_link:
	case DW_AT_use_location:
	case DW_AT_vtable_elem_location:
		switch (at->at_form) {
		case DW_FORM_data4:
		case DW_FORM_data8:
			/*
			 * DW_FORM_data[48] can not be used as section offset
			 * since DWARF4. For DWARF[23], the application needs
			 * to determine if DW_FORM_data[48] is representing
			 * a constant or a section offset.
			 */
			if (at->at_die->die_cu->cu_version >= 4) {
				DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
				return (DW_DLV_NO_ENTRY);
			}
			/* FALLTHROUGH */
		case DW_FORM_sec_offset:
			ret = _dwarf_loclist_find(dbg, at->at_die->die_cu,
			    at->u[0].u64, llbuf, listlen, NULL, error);
			if (ret == DW_DLE_NO_ENTRY) {
				DWARF_SET_ERROR(dbg, error, ret);
				return (DW_DLV_NO_ENTRY);
			}
			if (ret != DW_DLE_NONE)
				return (DW_DLV_ERROR);
			return (DW_DLV_OK);
		case DW_FORM_block:
		case DW_FORM_block1:
		case DW_FORM_block2:
		case DW_FORM_block4:
		case DW_FORM_exprloc:
			if (at->at_ld == NULL) {
				ret = _dwarf_loc_add(at->at_die, at, error);
				if (ret != DW_DLE_NONE)
					return (DW_DLV_ERROR);
			}
			*llbuf = calloc(1, sizeof(Dwarf_Locdesc *));
			if (*llbuf == NULL) {
				DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
				return (DW_DLV_ERROR);
			}
			(*llbuf)[0] = calloc(1, sizeof(Dwarf_Locdesc));
			if ((*llbuf)[0] == NULL) {
				free(*llbuf);
				DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
				return (DW_DLV_ERROR);
			}
			if (copy_locdesc(dbg, (*llbuf)[0], at->at_ld, error) !=
			    DW_DLE_NONE) {
				free((*llbuf)[0]);
				free(*llbuf);
				return (DW_DLV_ERROR);
			}
			*listlen = 1;
			return (DW_DLV_OK);
		default:
			/* Malformed Attr? */
			DWARF_SET_ERROR(dbg, error, DW_DLE_ATTR_FORM_BAD);
			return (DW_DLV_NO_ENTRY);
		}
	default:
		/* Wrong attr supplied. */
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}
}