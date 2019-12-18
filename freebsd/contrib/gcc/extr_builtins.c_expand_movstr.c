#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct insn_data {scalar_t__ (* genfun ) (scalar_t__,scalar_t__,scalar_t__) ;TYPE_1__* operand; } ;
typedef  scalar_t__ rtx ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 int CODE_FOR_movstr ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  HAVE_movstr ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ gen_lowpart (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ get_memory_rtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct insn_data* insn_data ; 
 scalar_t__ plus_constant (scalar_t__,int) ; 
 scalar_t__ replace_equiv_address (scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static rtx
expand_movstr (tree dest, tree src, rtx target, int endp)
{
  rtx end;
  rtx dest_mem;
  rtx src_mem;
  rtx insn;
  const struct insn_data * data;

  if (!HAVE_movstr)
    return 0;

  dest_mem = get_memory_rtx (dest, NULL);
  src_mem = get_memory_rtx (src, NULL);
  if (!endp)
    {
      target = force_reg (Pmode, XEXP (dest_mem, 0));
      dest_mem = replace_equiv_address (dest_mem, target);
      end = gen_reg_rtx (Pmode);
    }
  else
    {
      if (target == 0 || target == const0_rtx)
	{
	  end = gen_reg_rtx (Pmode);
	  if (target == 0)
	    target = end;
	}
      else
	end = target;
    }

  data = insn_data + CODE_FOR_movstr;

  if (data->operand[0].mode != VOIDmode)
    end = gen_lowpart (data->operand[0].mode, end);

  insn = data->genfun (end, dest_mem, src_mem);

  gcc_assert (insn);

  emit_insn (insn);

  /* movstr is supposed to set end to the address of the NUL
     terminator.  If the caller requested a mempcpy-like return value,
     adjust it.  */
  if (endp == 1 && target != const0_rtx)
    {
      rtx tem = plus_constant (gen_lowpart (GET_MODE (target), end), 1);
      emit_move_insn (target, force_operand (tem, NULL_RTX));
    }

  return target;
}