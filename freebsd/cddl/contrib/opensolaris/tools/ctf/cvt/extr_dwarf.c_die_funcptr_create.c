#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  t_flags; TYPE_2__* t_fndef; int /*<<< orphan*/  t_type; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_5__ {int fn_nargs; int fn_vargs; void** fn_args; void* fn_ret; } ;
typedef  TYPE_2__ fndef_t ;
typedef  int /*<<< orphan*/  dwarf_t ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  scalar_t__ Dwarf_Half ;
typedef  int /*<<< orphan*/ * Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_type ; 
 scalar_t__ DW_TAG_formal_parameter ; 
 scalar_t__ DW_TAG_unspecified_parameters ; 
 int /*<<< orphan*/  FUNCTION ; 
 int /*<<< orphan*/  TDESC_F_RESOLVED ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/ * die_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * die_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die_create_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ die_isdecl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* die_lookup_pass1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * die_sibling (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ die_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* tdesc_intr_void (int /*<<< orphan*/ *) ; 
 void* xcalloc (int) ; 

__attribute__((used)) static void
die_funcptr_create(dwarf_t *dw, Dwarf_Die die, Dwarf_Off off, tdesc_t *tdp)
{
	Dwarf_Attribute attr;
	Dwarf_Half tag;
	Dwarf_Die arg;
	fndef_t *fn;
	int i;

	debug(3, "die %llu <%llx>: creating function pointer\n", off, off);

	/*
	 * We'll begin by processing any type definition nodes that may be
	 * lurking underneath this one.
	 */
	for (arg = die_child(dw, die); arg != NULL;
	    arg = die_sibling(dw, arg)) {
		if ((tag = die_tag(dw, arg)) != DW_TAG_formal_parameter &&
		    tag != DW_TAG_unspecified_parameters) {
			/* Nested type declaration */
			die_create_one(dw, arg);
		}
	}

	if (die_isdecl(dw, die)) {
		/*
		 * This is a prototype.  We don't add prototypes to the
		 * tree, so we're going to drop the tdesc.  Unfortunately,
		 * it has already been added to the tree.  Nobody will reference
		 * it, though, and it will be leaked.
		 */
		return;
	}

	fn = xcalloc(sizeof (fndef_t));

	tdp->t_type = FUNCTION;

	if ((attr = die_attr(dw, die, DW_AT_type, 0)) != NULL) {
		fn->fn_ret = die_lookup_pass1(dw, die, DW_AT_type);
	} else {
		fn->fn_ret = tdesc_intr_void(dw);
	}

	/*
	 * Count the arguments to the function, then read them in.
	 */
	for (fn->fn_nargs = 0, arg = die_child(dw, die); arg != NULL;
	    arg = die_sibling(dw, arg)) {
		if ((tag = die_tag(dw, arg)) == DW_TAG_formal_parameter)
			fn->fn_nargs++;
		else if (tag == DW_TAG_unspecified_parameters &&
		    fn->fn_nargs > 0)
			fn->fn_vargs = 1;
	}

	if (fn->fn_nargs != 0) {
		debug(3, "die %llu: adding %d argument%s\n", off, fn->fn_nargs,
		    (fn->fn_nargs > 1 ? "s" : ""));

		fn->fn_args = xcalloc(sizeof (tdesc_t *) * fn->fn_nargs);
		for (i = 0, arg = die_child(dw, die);
		    arg != NULL && i < (int) fn->fn_nargs;
		    arg = die_sibling(dw, arg)) {
			if (die_tag(dw, arg) != DW_TAG_formal_parameter)
				continue;

			fn->fn_args[i++] = die_lookup_pass1(dw, arg,
			    DW_AT_type);
		}
	}

	tdp->t_fndef = fn;
	tdp->t_flags |= TDESC_F_RESOLVED;
}