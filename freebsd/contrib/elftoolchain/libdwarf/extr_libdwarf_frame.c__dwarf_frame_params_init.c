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
struct TYPE_3__ {int /*<<< orphan*/  dbg_frame_undefined_value; int /*<<< orphan*/  dbg_frame_same_value; int /*<<< orphan*/  dbg_frame_cfa_value; int /*<<< orphan*/  dbg_frame_rule_initial_value; int /*<<< orphan*/  dbg_frame_rule_table_size; } ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DW_FRAME_CFA_COL3 ; 
 int /*<<< orphan*/  DW_FRAME_LAST_REG_NUM ; 
 int /*<<< orphan*/  DW_FRAME_REG_INITIAL_VALUE ; 
 int /*<<< orphan*/  DW_FRAME_SAME_VAL ; 
 int /*<<< orphan*/  DW_FRAME_UNDEFINED_VAL ; 

void
_dwarf_frame_params_init(Dwarf_Debug dbg)
{

	/* Initialise call frame related parameters. */
	dbg->dbg_frame_rule_table_size = DW_FRAME_LAST_REG_NUM;
	dbg->dbg_frame_rule_initial_value = DW_FRAME_REG_INITIAL_VALUE;
	dbg->dbg_frame_cfa_value = DW_FRAME_CFA_COL3;
	dbg->dbg_frame_same_value = DW_FRAME_SAME_VAL;
	dbg->dbg_frame_undefined_value = DW_FRAME_UNDEFINED_VAL;
}