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
struct assign_parm_data_all {int /*<<< orphan*/  conversion_insns; scalar_t__ orig_fnargs; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {scalar_t__ (* split_complex_arg ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ COMPLEX_TYPE ; 
 scalar_t__ DECL_INCOMING_RTL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_MODE (scalar_t__) ; 
 scalar_t__ DECL_RTL (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 int GET_MODE_INNER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 int /*<<< orphan*/  SET_DECL_RTL (scalar_t__,scalar_t__) ; 
 scalar_t__ TREE_ADDRESSABLE (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ adjust_address_nv (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ assign_stack_local (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ gen_lowpart_SUBREG (int,scalar_t__) ; 
 scalar_t__ gen_rtx_CONCAT (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  int_size_in_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_to_sequence (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_decl_incoming_rtl (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_mem_attributes (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  set_mem_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
assign_parms_unsplit_complex (struct assign_parm_data_all *all, tree fnargs)
{
  tree parm;
  tree orig_fnargs = all->orig_fnargs;

  for (parm = orig_fnargs; parm; parm = TREE_CHAIN (parm))
    {
      if (TREE_CODE (TREE_TYPE (parm)) == COMPLEX_TYPE
	  && targetm.calls.split_complex_arg (TREE_TYPE (parm)))
	{
	  rtx tmp, real, imag;
	  enum machine_mode inner = GET_MODE_INNER (DECL_MODE (parm));

	  real = DECL_RTL (fnargs);
	  imag = DECL_RTL (TREE_CHAIN (fnargs));
	  if (inner != GET_MODE (real))
	    {
	      real = gen_lowpart_SUBREG (inner, real);
	      imag = gen_lowpart_SUBREG (inner, imag);
	    }

	  if (TREE_ADDRESSABLE (parm))
	    {
	      rtx rmem, imem;
	      HOST_WIDE_INT size = int_size_in_bytes (TREE_TYPE (parm));

	      /* split_complex_arg put the real and imag parts in
		 pseudos.  Move them to memory.  */
	      tmp = assign_stack_local (DECL_MODE (parm), size,
					TYPE_ALIGN (TREE_TYPE (parm)));
	      set_mem_attributes (tmp, parm, 1);
	      rmem = adjust_address_nv (tmp, inner, 0);
	      imem = adjust_address_nv (tmp, inner, GET_MODE_SIZE (inner));
	      push_to_sequence (all->conversion_insns);
	      emit_move_insn (rmem, real);
	      emit_move_insn (imem, imag);
	      all->conversion_insns = get_insns ();
	      end_sequence ();
	    }
	  else
	    tmp = gen_rtx_CONCAT (DECL_MODE (parm), real, imag);
	  SET_DECL_RTL (parm, tmp);

	  real = DECL_INCOMING_RTL (fnargs);
	  imag = DECL_INCOMING_RTL (TREE_CHAIN (fnargs));
	  if (inner != GET_MODE (real))
	    {
	      real = gen_lowpart_SUBREG (inner, real);
	      imag = gen_lowpart_SUBREG (inner, imag);
	    }
	  tmp = gen_rtx_CONCAT (DECL_MODE (parm), real, imag);
	  set_decl_incoming_rtl (parm, tmp);
	  fnargs = TREE_CHAIN (fnargs);
	}
      else
	{
	  SET_DECL_RTL (parm, DECL_RTL (fnargs));
	  set_decl_incoming_rtl (parm, DECL_INCOMING_RTL (fnargs));

	  /* Set MEM_EXPR to the original decl, i.e. to PARM,
	     instead of the copy of decl, i.e. FNARGS.  */
	  if (DECL_INCOMING_RTL (parm) && MEM_P (DECL_INCOMING_RTL (parm)))
	    set_mem_expr (DECL_INCOMING_RTL (parm), parm);
	}

      fnargs = TREE_CHAIN (fnargs);
    }
}