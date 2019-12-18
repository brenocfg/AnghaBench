#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct cgraph_varpool_node {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {scalar_t__ (* ttype ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 int BITS_PER_UNIT ; 
 int DW_EH_PE_absptr ; 
 int DW_EH_PE_aligned ; 
 int /*<<< orphan*/  EXPAND_INITIALIZER ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int TREE_PUBLIC (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  assemble_integer (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  cgraph_varpool_mark_needed_node (struct cgraph_varpool_node*) ; 
 struct cgraph_varpool_node* cgraph_varpool_node (scalar_t__) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  dw2_asm_output_encoded_addr_rtx (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expand_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ lookup_type_for_runtime (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
output_ttype (tree type, int tt_format, int tt_format_size)
{
  rtx value;
  bool public = true;

  if (type == NULL_TREE)
    value = const0_rtx;
  else
    {
      struct cgraph_varpool_node *node;

      type = lookup_type_for_runtime (type);
      value = expand_expr (type, NULL_RTX, VOIDmode, EXPAND_INITIALIZER);

      /* Let cgraph know that the rtti decl is used.  Not all of the
	 paths below go through assemble_integer, which would take
	 care of this for us.  */
      STRIP_NOPS (type);
      if (TREE_CODE (type) == ADDR_EXPR)
	{
	  type = TREE_OPERAND (type, 0);
	  if (TREE_CODE (type) == VAR_DECL)
	    {
	      node = cgraph_varpool_node (type);
	      if (node)
		cgraph_varpool_mark_needed_node (node);
	      public = TREE_PUBLIC (type);
	    }
	}
      else
	gcc_assert (TREE_CODE (type) == INTEGER_CST);
    }

  /* Allow the target to override the type table entry format.  */
  if (targetm.asm_out.ttype (value))
    return;

  if (tt_format == DW_EH_PE_absptr || tt_format == DW_EH_PE_aligned)
    assemble_integer (value, tt_format_size,
		      tt_format_size * BITS_PER_UNIT, 1);
  else
    dw2_asm_output_encoded_addr_rtx (tt_format, value, public, NULL);
}