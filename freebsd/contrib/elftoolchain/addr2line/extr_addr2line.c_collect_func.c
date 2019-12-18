#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct Func {void* call_file; void* call_line; struct Func* inlined_caller; void* hipc; void* lopc; scalar_t__ ranges_cnt; int /*<<< orphan*/ * ranges; int /*<<< orphan*/ * name; } ;
struct CU {int /*<<< orphan*/  funclist; } ;
typedef  void* Dwarf_Unsigned ;
typedef  scalar_t__ Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Ranges ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  scalar_t__ Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_abstract_origin ; 
 int /*<<< orphan*/  DW_AT_call_file ; 
 int /*<<< orphan*/  DW_AT_call_line ; 
 int /*<<< orphan*/  DW_AT_high_pc ; 
 int /*<<< orphan*/  DW_AT_low_pc ; 
 int /*<<< orphan*/  DW_AT_name ; 
 int /*<<< orphan*/  DW_AT_ranges ; 
 int /*<<< orphan*/  DW_AT_specification ; 
 int /*<<< orphan*/  DW_DLA_DIE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 scalar_t__ DW_TAG_entry_point ; 
 scalar_t__ DW_TAG_inlined_subroutine ; 
 scalar_t__ DW_TAG_subprogram ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct Func*,int /*<<< orphan*/ ) ; 
 struct Func* calloc (int,int) ; 
 int dwarf_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_attrval_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int dwarf_attrval_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int dwarf_child (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_errmsg (int /*<<< orphan*/ ) ; 
 int dwarf_get_ranges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_global_formref (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_offdie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int dwarf_siblingof (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_tag (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int handle_high_pc (int /*<<< orphan*/ *,void*,void**) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
collect_func(Dwarf_Debug dbg, Dwarf_Die die, struct Func *parent, struct CU *cu)
{
	Dwarf_Die ret_die, abst_die, spec_die;
	Dwarf_Error de;
	Dwarf_Half tag;
	Dwarf_Unsigned lopc, hipc, ranges_off;
	Dwarf_Signed ranges_cnt;
	Dwarf_Off ref;
	Dwarf_Attribute abst_at, spec_at;
	Dwarf_Ranges *ranges;
	const char *funcname;
	struct Func *f;
	int found_ranges, ret;

	f = NULL;
	abst_die = spec_die = NULL;

	if (dwarf_tag(die, &tag, &de)) {
		warnx("dwarf_tag: %s", dwarf_errmsg(de));
		goto cont_search;
	}
	if (tag == DW_TAG_subprogram || tag == DW_TAG_entry_point ||
	    tag == DW_TAG_inlined_subroutine) {
		/*
		 * Function address range can be specified by either
		 * a DW_AT_ranges attribute which points to a range list or
		 * by a pair of DW_AT_low_pc and DW_AT_high_pc attributes.
		 */
		ranges = NULL;
		ranges_cnt = 0;
		found_ranges = 0;
		if (dwarf_attrval_unsigned(die, DW_AT_ranges, &ranges_off,
		    &de) == DW_DLV_OK &&
		    dwarf_get_ranges(dbg, (Dwarf_Off) ranges_off, &ranges,
		    &ranges_cnt, NULL, &de) == DW_DLV_OK) {
			if (ranges != NULL && ranges_cnt > 0) {
				found_ranges = 1;
				goto get_func_name;
			}
		}

		/*
		 * Search for DW_AT_low_pc/DW_AT_high_pc if ranges pointer
		 * not found.
		 */
		if (dwarf_attrval_unsigned(die, DW_AT_low_pc, &lopc, &de) ||
		    dwarf_attrval_unsigned(die, DW_AT_high_pc, &hipc, &de))
			goto cont_search;
		if (handle_high_pc(die, lopc, &hipc) != DW_DLV_OK)
			goto cont_search;

	get_func_name:
		/*
		 * Most common case the function name is stored in DW_AT_name
		 * attribute.
		 */
		if (dwarf_attrval_string(die, DW_AT_name, &funcname, &de) ==
		    DW_DLV_OK)
			goto add_func;

		/*
		 * For inlined function, the actual name is probably in the DIE
		 * referenced by DW_AT_abstract_origin. (if present)
		 */
		if (dwarf_attr(die, DW_AT_abstract_origin, &abst_at, &de) ==
		    DW_DLV_OK &&
		    dwarf_global_formref(abst_at, &ref, &de) == DW_DLV_OK &&
		    dwarf_offdie(dbg, ref, &abst_die, &de) == DW_DLV_OK &&
		    dwarf_attrval_string(abst_die, DW_AT_name, &funcname,
		    &de) == DW_DLV_OK)
			goto add_func;

		/*
		 * If DW_AT_name is not present, but DW_AT_specification is
		 * present, then probably the actual name is in the DIE
		 * referenced by DW_AT_specification.
		 */
		if (dwarf_attr(die, DW_AT_specification, &spec_at, &de) ==
		    DW_DLV_OK &&
		    dwarf_global_formref(spec_at, &ref, &de) == DW_DLV_OK &&
		    dwarf_offdie(dbg, ref, &spec_die, &de) == DW_DLV_OK &&
		    dwarf_attrval_string(spec_die, DW_AT_name, &funcname,
		    &de) == DW_DLV_OK)
			goto add_func;

		/* Skip if no name associated with this DIE. */
		goto cont_search;

	add_func:
		if ((f = calloc(1, sizeof(*f))) == NULL)
			err(EXIT_FAILURE, "calloc");
		if ((f->name = strdup(funcname)) == NULL)
			err(EXIT_FAILURE, "strdup");
		if (found_ranges) {
			f->ranges = ranges;
			f->ranges_cnt = ranges_cnt;
		} else {
			f->lopc = lopc;
			f->hipc = hipc;
		}
		if (tag == DW_TAG_inlined_subroutine) {
			f->inlined_caller = parent;
			dwarf_attrval_unsigned(die, DW_AT_call_file,
			    &f->call_file, &de);
			dwarf_attrval_unsigned(die, DW_AT_call_line,
			    &f->call_line, &de);
		}
		STAILQ_INSERT_TAIL(&cu->funclist, f, next);
	}

cont_search:

	/* Search children. */
	ret = dwarf_child(die, &ret_die, &de);
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_child: %s", dwarf_errmsg(de));
	else if (ret == DW_DLV_OK) {
		if (f != NULL)
			collect_func(dbg, ret_die, f, cu);
		else
			collect_func(dbg, ret_die, parent, cu);
	}

	/* Search sibling. */
	ret = dwarf_siblingof(dbg, die, &ret_die, &de);
	if (ret == DW_DLV_ERROR)
		warnx("dwarf_siblingof: %s", dwarf_errmsg(de));
	else if (ret == DW_DLV_OK)
		collect_func(dbg, ret_die, parent, cu);

	/* Cleanup */
	dwarf_dealloc(dbg, die, DW_DLA_DIE);

	if (abst_die != NULL)
		dwarf_dealloc(dbg, abst_die, DW_DLA_DIE);

	if (spec_die != NULL)
		dwarf_dealloc(dbg, spec_die, DW_DLA_DIE);
}