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
typedef  int /*<<< orphan*/  tree ;
struct eh_region {scalar_t__ resume; } ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int /*<<< orphan*/  region_array; } ;

/* Variables and functions */
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VOIDmode ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  eh_region ; 
 int /*<<< orphan*/  emit_barrier () ; 
 scalar_t__ emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_RESX (int /*<<< orphan*/ ,int) ; 

void
expand_resx_expr (tree exp)
{
  int region_nr = TREE_INT_CST_LOW (TREE_OPERAND (exp, 0));
  struct eh_region *reg = VEC_index (eh_region,
				     cfun->eh->region_array, region_nr);

  gcc_assert (!reg->resume);
  reg->resume = emit_jump_insn (gen_rtx_RESX (VOIDmode, region_nr));
  emit_barrier ();
}