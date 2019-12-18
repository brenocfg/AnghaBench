#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pubname_callback_param {int found; int /*<<< orphan*/  sp_die; scalar_t__ file; int /*<<< orphan*/  cu_die; int /*<<< orphan*/  function; } ;
struct TYPE_3__ {int /*<<< orphan*/  cu_offset; int /*<<< orphan*/  die_offset; } ;
typedef  TYPE_1__ Dwarf_Global ;
typedef  int /*<<< orphan*/  Dwarf ;

/* Variables and functions */
 int DWARF_CB_ABORT ; 
 int DWARF_CB_OK ; 
 scalar_t__ DW_TAG_subprogram ; 
 scalar_t__ die_compare_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_decl_file (int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_offdie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ strtailcmp (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pubname_search_cb(Dwarf *dbg, Dwarf_Global *gl, void *data)
{
	struct pubname_callback_param *param = data;

	if (dwarf_offdie(dbg, gl->die_offset, param->sp_die)) {
		if (dwarf_tag(param->sp_die) != DW_TAG_subprogram)
			return DWARF_CB_OK;

		if (die_compare_name(param->sp_die, param->function)) {
			if (!dwarf_offdie(dbg, gl->cu_offset, param->cu_die))
				return DWARF_CB_OK;

			if (param->file &&
			    strtailcmp(param->file, dwarf_decl_file(param->sp_die)))
				return DWARF_CB_OK;

			param->found = 1;
			return DWARF_CB_ABORT;
		}
	}

	return DWARF_CB_OK;
}