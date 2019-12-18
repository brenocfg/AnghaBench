#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {int /*<<< orphan*/ * regs; } ;
typedef  TYPE_1__ dataflow_set ;
struct TYPE_5__ {TYPE_1__ out; } ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ BLKmode ; 
 scalar_t__ DECL_ARGUMENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_INCOMING_RTL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  DECL_RTL_IF_SET (scalar_t__) ; 
 int /*<<< orphan*/  ENTRY_BLOCK_PTR ; 
 size_t FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PARM_DECL ; 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 TYPE_3__* VTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attrs_list_insert (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  set_variable_part (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_get_decl_and_offset (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vt_add_function_parameters (void)
{
  tree parm;
  
  for (parm = DECL_ARGUMENTS (current_function_decl);
       parm; parm = TREE_CHAIN (parm))
    {
      rtx decl_rtl = DECL_RTL_IF_SET (parm);
      rtx incoming = DECL_INCOMING_RTL (parm);
      tree decl;
      HOST_WIDE_INT offset;
      dataflow_set *out;

      if (TREE_CODE (parm) != PARM_DECL)
	continue;

      if (!DECL_NAME (parm))
	continue;

      if (!decl_rtl || !incoming)
	continue;

      if (GET_MODE (decl_rtl) == BLKmode || GET_MODE (incoming) == BLKmode)
	continue;

      if (!vt_get_decl_and_offset (incoming, &decl, &offset))
	if (!vt_get_decl_and_offset (decl_rtl, &decl, &offset))
	  continue;

      if (!decl)
	continue;

      gcc_assert (parm == decl);

      out = &VTI (ENTRY_BLOCK_PTR)->out;

      if (REG_P (incoming))
	{
	  gcc_assert (REGNO (incoming) < FIRST_PSEUDO_REGISTER);
	  attrs_list_insert (&out->regs[REGNO (incoming)],
			     parm, offset, incoming);
	  set_variable_part (out, incoming, parm, offset);
	}
      else if (MEM_P (incoming))
	set_variable_part (out, incoming, parm, offset);
    }
}