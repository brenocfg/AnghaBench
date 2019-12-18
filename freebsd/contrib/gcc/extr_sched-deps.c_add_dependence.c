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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum reg_note { ____Placeholder_reg_note } reg_note ;
typedef  int /*<<< orphan*/  ds_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEP_ANTI ; 
 int /*<<< orphan*/  DEP_OUTPUT ; 
 int /*<<< orphan*/  DEP_TRUE ; 
 int REG_DEP_ANTI ; 
 int REG_DEP_OUTPUT ; 
 int REG_DEP_TRUE ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  maybe_add_or_update_back_dep_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
add_dependence (rtx insn, rtx elem, enum reg_note dep_type)
{
  ds_t ds;
  
  if (dep_type == REG_DEP_TRUE)
    ds = DEP_TRUE;
  else if (dep_type == REG_DEP_OUTPUT)
    ds = DEP_OUTPUT;
  else if (dep_type == REG_DEP_ANTI)
    ds = DEP_ANTI;
  else
    gcc_unreachable ();

  maybe_add_or_update_back_dep_1 (insn, elem, dep_type, ds, 0, 0, 0);
}