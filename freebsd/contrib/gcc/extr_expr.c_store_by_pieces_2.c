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
struct store_by_pieces {unsigned int len; unsigned int offset; scalar_t__ explicit_inc_to; scalar_t__ reverse; int /*<<< orphan*/  to_addr; int /*<<< orphan*/  constfundata; int /*<<< orphan*/  (* constfun ) (int /*<<< orphan*/ ,unsigned int,int) ;int /*<<< orphan*/  to; scalar_t__ autinc_to; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  unsigned int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (unsigned int) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 scalar_t__ HAVE_POST_INCREMENT ; 
 scalar_t__ HAVE_PRE_DECREMENT ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  adjust_automodify_address (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  emit_insn (rtx) ; 
 rtx gen_add2_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,int) ; 
 rtx stub2 (rtx,...) ; 

__attribute__((used)) static void
store_by_pieces_2 (rtx (*genfun) (rtx, ...), enum machine_mode mode,
		   struct store_by_pieces *data)
{
  unsigned int size = GET_MODE_SIZE (mode);
  rtx to1, cst;

  while (data->len >= size)
    {
      if (data->reverse)
	data->offset -= size;

      if (data->autinc_to)
	to1 = adjust_automodify_address (data->to, mode, data->to_addr,
					 data->offset);
      else
	to1 = adjust_address (data->to, mode, data->offset);

      if (HAVE_PRE_DECREMENT && data->explicit_inc_to < 0)
	emit_insn (gen_add2_insn (data->to_addr,
				  GEN_INT (-(HOST_WIDE_INT) size)));

      cst = (*data->constfun) (data->constfundata, data->offset, mode);
      emit_insn ((*genfun) (to1, cst));

      if (HAVE_POST_INCREMENT && data->explicit_inc_to > 0)
	emit_insn (gen_add2_insn (data->to_addr, GEN_INT (size)));

      if (! data->reverse)
	data->offset += size;

      data->len -= size;
    }
}