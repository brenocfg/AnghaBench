#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  dw_regnum; } ;
struct TYPE_13__ {int /*<<< orphan*/  cie_daf; int /*<<< orphan*/  cie_caf; int /*<<< orphan*/  cie_addrsize; int /*<<< orphan*/  cie_instlen; int /*<<< orphan*/  cie_initinst; } ;
struct TYPE_12__ {int /*<<< orphan*/  dbg_frame_rule_initial_value; TYPE_1__* dbg_internal_reg_table; } ;
struct TYPE_11__ {unsigned long long fde_initloc; int /*<<< orphan*/  fde_instlen; int /*<<< orphan*/  fde_inst; TYPE_4__* fde_cie; TYPE_3__* fde_dbg; } ;
struct TYPE_10__ {int rt3_reg_table_size; TYPE_5__* rt3_rules; TYPE_5__ rt3_cfa_rule; } ;
typedef  int /*<<< orphan*/  Dwarf_Regtable_Entry3 ;
typedef  TYPE_1__ Dwarf_Regtable3 ;
typedef  TYPE_2__* Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_3__* Dwarf_Debug ;
typedef  TYPE_4__* Dwarf_Cie ;
typedef  unsigned long long Dwarf_Addr ;

/* Variables and functions */
 int DW_DLE_NONE ; 
 int _dwarf_frame_run_inst (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long,unsigned long long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

int
_dwarf_frame_get_internal_table(Dwarf_Fde fde, Dwarf_Addr pc_req,
    Dwarf_Regtable3 **ret_rt, Dwarf_Addr *ret_row_pc, Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	Dwarf_Cie cie;
	Dwarf_Regtable3 *rt;
	Dwarf_Addr row_pc;
	int i, ret;

	assert(ret_rt != NULL);

	dbg = fde->fde_dbg;
	assert(dbg != NULL);

	rt = dbg->dbg_internal_reg_table;

	/* Clear the content of regtable from previous run. */
	memset(&rt->rt3_cfa_rule, 0, sizeof(Dwarf_Regtable_Entry3));
	memset(rt->rt3_rules, 0, rt->rt3_reg_table_size *
	    sizeof(Dwarf_Regtable_Entry3));

	/* Set rules to initial values. */
	for (i = 0; i < rt->rt3_reg_table_size; i++)
		rt->rt3_rules[i].dw_regnum = dbg->dbg_frame_rule_initial_value;

	/* Run initial instructions in CIE. */
	cie = fde->fde_cie;
	assert(cie != NULL);
	ret = _dwarf_frame_run_inst(dbg, rt, cie->cie_addrsize,
	    cie->cie_initinst, cie->cie_instlen, cie->cie_caf, cie->cie_daf, 0,
	    ~0ULL, &row_pc, error);
	if (ret != DW_DLE_NONE)
		return (ret);

	/* Run instructions in FDE. */
	if (pc_req >= fde->fde_initloc) {
		ret = _dwarf_frame_run_inst(dbg, rt, cie->cie_addrsize,
		    fde->fde_inst, fde->fde_instlen, cie->cie_caf,
		    cie->cie_daf, fde->fde_initloc, pc_req, &row_pc, error);
		if (ret != DW_DLE_NONE)
			return (ret);
	}

	*ret_rt = rt;
	*ret_row_pc = row_pc;

	return (DW_DLE_NONE);
}