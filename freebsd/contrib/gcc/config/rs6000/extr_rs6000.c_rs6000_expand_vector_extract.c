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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_INNER (int) ; 
 int GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  UNSPEC_STVE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  adjust_address_nv (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assign_stack_temp (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rs6000_expand_vector_extract (rtx target, rtx vec, int elt)
{
  enum machine_mode mode = GET_MODE (vec);
  enum machine_mode inner_mode = GET_MODE_INNER (mode);
  rtx mem, x;

  /* Allocate mode-sized buffer.  */
  mem = assign_stack_temp (mode, GET_MODE_SIZE (mode), 0);

  /* Add offset to field within buffer matching vector element.  */
  mem = adjust_address_nv (mem, mode, elt * GET_MODE_SIZE (inner_mode));

  /* Store single field into mode-sized buffer.  */
  x = gen_rtx_UNSPEC (VOIDmode,
		      gen_rtvec (1, const0_rtx), UNSPEC_STVE);
  emit_insn (gen_rtx_PARALLEL (VOIDmode,
			       gen_rtvec (2,
					  gen_rtx_SET (VOIDmode,
						       mem, vec),
					  x)));
  emit_move_insn (target, adjust_address_nv (mem, inner_mode, 0));
}