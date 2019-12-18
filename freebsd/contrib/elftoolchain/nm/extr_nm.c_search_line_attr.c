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
typedef  scalar_t__ uint8_t ;
struct var_info_head {int dummy; } ;
struct var_info_entry {int line; int lowpc; int highpc; struct var_info_entry* file; int /*<<< orphan*/ * name; int /*<<< orphan*/  addr; } ;
typedef  struct var_info_head func_info_head ;
struct func_info_entry {int line; int lowpc; int highpc; struct func_info_entry* file; int /*<<< orphan*/ * name; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {scalar_t__ bl_data; } ;
typedef  int Dwarf_Unsigned ;
typedef  scalar_t__ Dwarf_Signed ;
typedef  scalar_t__ Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;
typedef  scalar_t__ Dwarf_Bool ;
typedef  TYPE_1__ Dwarf_Block ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_artificial ; 
 int /*<<< orphan*/  DW_AT_decl_file ; 
 int /*<<< orphan*/  DW_AT_decl_line ; 
 int /*<<< orphan*/  DW_AT_declaration ; 
 int /*<<< orphan*/  DW_AT_external ; 
 int /*<<< orphan*/  DW_AT_high_pc ; 
 int /*<<< orphan*/  DW_AT_location ; 
 int /*<<< orphan*/  DW_AT_low_pc ; 
 int /*<<< orphan*/  DW_DLA_DIE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 scalar_t__ DW_OP_addr ; 
 scalar_t__ DW_TAG_entry_point ; 
 scalar_t__ DW_TAG_inlined_subroutine ; 
 scalar_t__ DW_TAG_subprogram ; 
 scalar_t__ DW_TAG_variable ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct var_info_head*,struct var_info_entry*,int /*<<< orphan*/ ) ; 
 struct var_info_entry* calloc (int,int) ; 
 int dwarf_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_attrval_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dwarf_attrval_unsigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int dwarf_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 int dwarf_formblock (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int dwarf_siblingof (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_tag (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entries ; 
 void* find_object_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct var_info_entry*) ; 
 int /*<<< orphan*/  get_block_value (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
search_line_attr(Dwarf_Debug dbg, struct func_info_head *func_info,
    struct var_info_head *var_info, Dwarf_Die die, char **src_files,
    Dwarf_Signed filecount)
{
	Dwarf_Attribute at;
	Dwarf_Unsigned udata;
	Dwarf_Half tag;
	Dwarf_Block *block;
	Dwarf_Bool flag;
	Dwarf_Die ret_die;
	Dwarf_Error de;
	struct func_info_entry *func;
	struct var_info_entry *var;
	int ret;

	if (dwarf_tag(die, &tag, &de) != DW_DLV_OK) {
		warnx("dwarf_tag failed: %s", dwarf_errmsg(de));
		goto cont_search;
	}

	/* We're interested in DIEs which define functions or variables. */
	if (tag != DW_TAG_subprogram && tag != DW_TAG_entry_point &&
	    tag != DW_TAG_inlined_subroutine && tag != DW_TAG_variable)
		goto cont_search;

	if (tag == DW_TAG_variable) {

		/* Ignore "artificial" variable. */
		if (dwarf_attrval_flag(die, DW_AT_artificial, &flag, &de) ==
		    DW_DLV_OK && flag)
			goto cont_search;

		/* Ignore pure declaration. */
		if (dwarf_attrval_flag(die, DW_AT_declaration, &flag, &de) ==
		    DW_DLV_OK && flag)
			goto cont_search;

		/* Ignore stack varaibles. */
		if (dwarf_attrval_flag(die, DW_AT_external, &flag, &de) !=
		    DW_DLV_OK || !flag)
			goto cont_search;

		if ((var = calloc(1, sizeof(*var))) == NULL) {
			warn("calloc failed");
			goto cont_search;
		}

		if (dwarf_attrval_unsigned(die, DW_AT_decl_file, &udata,
		    &de) == DW_DLV_OK && udata > 0 &&
		    (Dwarf_Signed) (udata - 1) < filecount) {
			var->file = strdup(src_files[udata - 1]);
			if (var->file == NULL) {
				warn("strdup");
				free(var);
				goto cont_search;
			}
		}

		if (dwarf_attrval_unsigned(die, DW_AT_decl_line, &udata, &de) ==
		    DW_DLV_OK)
			var->line = udata;

		var->name = find_object_name(dbg, die);
		if (var->name == NULL) {
			if (var->file)
				free(var->file);
			free(var);
			goto cont_search;
		}

		if (dwarf_attr(die, DW_AT_location, &at, &de) == DW_DLV_OK &&
		    dwarf_formblock(at, &block, &de) == DW_DLV_OK) {
			/*
			 * Since we ignored stack variables, the rest are the
			 * external varaibles which should always use DW_OP_addr
			 * operator for DW_AT_location value.
			 */
			if (*((uint8_t *)block->bl_data) == DW_OP_addr)
				var->addr = get_block_value(dbg, block);
		}

		SLIST_INSERT_HEAD(var_info, var, entries);

	} else {

		if ((func = calloc(1, sizeof(*func))) == NULL) {
			warn("calloc failed");
			goto cont_search;
		}

		/*
		 * Note that dwarf_attrval_unsigned() handles DW_AT_abstract_origin
		 * internally, so it can retrieve DW_AT_decl_file/DW_AT_decl_line
		 * attributes for inlined functions as well.
		 */
		if (dwarf_attrval_unsigned(die, DW_AT_decl_file, &udata,
		    &de) == DW_DLV_OK && udata > 0 &&
		    (Dwarf_Signed) (udata - 1) < filecount) {
			func->file = strdup(src_files[udata - 1]);
			if (func->file == NULL) {
				warn("strdup");
				free(func);
				goto cont_search;
			}
		}

		if (dwarf_attrval_unsigned(die, DW_AT_decl_line, &udata, &de) ==
		    DW_DLV_OK)
			func->line = udata;

		func->name = find_object_name(dbg, die);
		if (func->name == NULL) {
			if (func->file)
				free(func->file);
			free(func);
			goto cont_search;
		}

		if (dwarf_attrval_unsigned(die, DW_AT_low_pc, &udata, &de) ==
		    DW_DLV_OK)
			func->lowpc = udata;
		if (dwarf_attrval_unsigned(die, DW_AT_high_pc, &udata, &de) ==
		    DW_DLV_OK)
			func->highpc = udata;

		SLIST_INSERT_HEAD(func_info, func, entries);
	}

cont_search:

	/* Search children. */
	ret = dwarf_child(die, &ret_die, &de);
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_child: %s", dwarf_errmsg(de));
	else if (ret == DW_DLV_OK)
		search_line_attr(dbg, func_info, var_info, ret_die, src_files,
		    filecount);

	/* Search sibling. */
	ret = dwarf_siblingof(dbg, die, &ret_die, &de);
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_siblingof: %s", dwarf_errmsg(de));
	else if (ret == DW_DLV_OK)
		search_line_attr(dbg, func_info, var_info, ret_die, src_files,
		    filecount);

	dwarf_dealloc(dbg, die, DW_DLA_DIE);
}