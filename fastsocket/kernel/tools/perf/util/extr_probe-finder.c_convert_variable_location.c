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
struct probe_trace_arg {int /*<<< orphan*/ * ref; int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {scalar_t__ atom; unsigned int number; unsigned int number2; } ;
typedef  unsigned int Dwarf_Word ;
typedef  TYPE_1__ Dwarf_Op ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_external ; 
 int /*<<< orphan*/  DW_AT_location ; 
 scalar_t__ DW_OP_addr ; 
 scalar_t__ DW_OP_breg0 ; 
 scalar_t__ DW_OP_breg31 ; 
 scalar_t__ DW_OP_bregx ; 
 scalar_t__ DW_OP_fbreg ; 
 scalar_t__ DW_OP_reg0 ; 
 scalar_t__ DW_OP_reg31 ; 
 scalar_t__ DW_OP_regx ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int ERANGE ; 
 void* alloc_trace_arg_ref (long) ; 
 int /*<<< orphan*/ * dwarf_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_getlocation_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**,size_t*,int) ; 
 char* get_arch_regstr (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_warning (char*,unsigned int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * zalloc (int) ; 

__attribute__((used)) static int convert_variable_location(Dwarf_Die *vr_die, Dwarf_Addr addr,
				     Dwarf_Op *fb_ops,
				     struct probe_trace_arg *tvar)
{
	Dwarf_Attribute attr;
	Dwarf_Op *op;
	size_t nops;
	unsigned int regn;
	Dwarf_Word offs = 0;
	bool ref = false;
	const char *regs;
	int ret;

	if (dwarf_attr(vr_die, DW_AT_external, &attr) != NULL)
		goto static_var;

	/* TODO: handle more than 1 exprs */
	if (dwarf_attr(vr_die, DW_AT_location, &attr) == NULL ||
	    dwarf_getlocation_addr(&attr, addr, &op, &nops, 1) <= 0 ||
	    nops == 0) {
		/* TODO: Support const_value */
		return -ENOENT;
	}

	if (op->atom == DW_OP_addr) {
static_var:
		if (!tvar)
			return 0;
		/* Static variables on memory (not stack), make @varname */
		ret = strlen(dwarf_diename(vr_die));
		tvar->value = zalloc(ret + 2);
		if (tvar->value == NULL)
			return -ENOMEM;
		snprintf(tvar->value, ret + 2, "@%s", dwarf_diename(vr_die));
		tvar->ref = alloc_trace_arg_ref((long)offs);
		if (tvar->ref == NULL)
			return -ENOMEM;
		return 0;
	}

	/* If this is based on frame buffer, set the offset */
	if (op->atom == DW_OP_fbreg) {
		if (fb_ops == NULL)
			return -ENOTSUP;
		ref = true;
		offs = op->number;
		op = &fb_ops[0];
	}

	if (op->atom >= DW_OP_breg0 && op->atom <= DW_OP_breg31) {
		regn = op->atom - DW_OP_breg0;
		offs += op->number;
		ref = true;
	} else if (op->atom >= DW_OP_reg0 && op->atom <= DW_OP_reg31) {
		regn = op->atom - DW_OP_reg0;
	} else if (op->atom == DW_OP_bregx) {
		regn = op->number;
		offs += op->number2;
		ref = true;
	} else if (op->atom == DW_OP_regx) {
		regn = op->number;
	} else {
		pr_debug("DW_OP %x is not supported.\n", op->atom);
		return -ENOTSUP;
	}

	if (!tvar)
		return 0;

	regs = get_arch_regstr(regn);
	if (!regs) {
		/* This should be a bug in DWARF or this tool */
		pr_warning("Mapping for the register number %u "
			   "missing on this architecture.\n", regn);
		return -ERANGE;
	}

	tvar->value = strdup(regs);
	if (tvar->value == NULL)
		return -ENOMEM;

	if (ref) {
		tvar->ref = alloc_trace_arg_ref((long)offs);
		if (tvar->ref == NULL)
			return -ENOMEM;
	}
	return 0;
}