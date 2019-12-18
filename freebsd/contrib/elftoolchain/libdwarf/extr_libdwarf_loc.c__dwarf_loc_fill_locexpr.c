#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {unsigned long long ld_hipc; int /*<<< orphan*/ * ld_s; scalar_t__ ld_lopc; } ;
typedef  TYPE_1__ Dwarf_Locdesc ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int _dwarf_loc_fill_locdesc (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 

int
_dwarf_loc_fill_locexpr(Dwarf_Debug dbg, Dwarf_Locdesc **ret_llbuf, uint8_t *in,
    uint64_t in_len, uint8_t pointer_size, uint8_t offset_size,
    uint8_t version, Dwarf_Error *error)
{
	Dwarf_Locdesc *llbuf;
	int ret;

	if ((llbuf = malloc(sizeof(Dwarf_Locdesc))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}
	llbuf->ld_lopc = 0;
	llbuf->ld_hipc = ~0ULL;
	llbuf->ld_s = NULL;

	ret = _dwarf_loc_fill_locdesc(dbg, llbuf, in, in_len, pointer_size,
	    offset_size, version, error);
	if (ret != DW_DLE_NONE) {
		free(llbuf);
		return (ret);
	}

	*ret_llbuf = llbuf;

	return (ret);
}